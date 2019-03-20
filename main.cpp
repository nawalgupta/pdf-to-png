#include <iostream>
#include <poppler-document.h>
#include <poppler-page.h>
#include <poppler-page-renderer.h>
#include <poppler-image.h>
#include <png++/image.hpp>
#include <png++/png.hpp>
#include <memory>


int main(){

    std::string file_name;

    std::cout<<"File's address: ";

    if(!(std::cin>>file_name)){

        std::cerr<<"Error\n";

        return 1;
    }

    double DPI=10;

    //Compress the miniature of the page by the small dpi.

    std::unique_ptr<poppler::document>my_pdf(poppler::document::load_from_file(file_name));

    std::cout<<"This file has "<<my_pdf->pages()<<" pages.\n";

    int count;

    std::cout<<"Choose:\n 1. One page PDF->PNG.\n 2. Save the whole file in png image.\n";

    if(!(std::cin>>count)){

        std::cerr<<"Error\n";

        return 1;
    }

    switch(count)

    {
     case 1:{

        size_t i;

        std::cout<<"Enter a number of page: ";

        if(!(std::cin>>i)){

            std::cerr<<"Error\n";

            return 1;

        }

        --i;


        std::unique_ptr<poppler::page>my_page(my_pdf->create_page(i));

        poppler::page_renderer renderer;

        renderer.set_render_hint(poppler::page_renderer::text_antialiasing);

        poppler::image my_image=renderer.render_page(my_page.get(),DPI,DPI);

        std::string file_out;

        std::cout<<"Address of saving: ";

        if(!(std::cin>>file_out)){

            std::cerr<<"Error\n";

            return 1;

        }

        my_image.save(file_out,"png");

        break;

    }

    case 2:{

        std::string file_out;

        std::cout<<"Address of saving: ";

        if(!(std::cin>>file_out)){

          std::cerr<<"Error\n";

          return 1;

        }

        std::unique_ptr<poppler::page>my_page(my_pdf->create_page(0));

        poppler::page_renderer renderer;

        renderer.set_render_hint(poppler::page_renderer::text_antialiasing);

        poppler::image my_image=renderer.render_page(my_page.get(),DPI,DPI);

        my_image.save(file_out,"png");

        png::image<png::rgb_pixel>full_image(((my_pdf->pages()*my_image.width())+160),140+(my_image.height()*2));//Constructs an empty image of specified width and height.

        for(int i=0;i<full_image.get_width();++i){


            for(int j=0;j<full_image.get_height();++j){

                png::rgb_pixel pixel_new=full_image.get_pixel(i,j);

                pixel_new.red+=155;

                pixel_new.green+=200;

                pixel_new.blue+=200;

                full_image.set_pixel(i,j,pixel_new);

                }

            }



        for(size_t i=0;i<my_pdf->pages();++i){

               size_t f=i;

               ++f;

               if(i>=1)

               {
                   std::unique_ptr<poppler::page>my_page(my_pdf->create_page(i));

                   poppler::page_renderer renderer;

                   renderer.set_render_hint(poppler::page_renderer::text_antialiasing);

                   poppler::image my_image=renderer.render_page(my_page.get(),DPI,DPI);

                   my_image.save(file_out,"png");

               }

               png::image<png::rgb_pixel>image_png(file_out);

               size_t w=(i*image_png.get_width())+75;

               size_t h=(f*image_png.get_width())+70;

                  for(size_t k=w;k<h;++k){

                      for(size_t j=70;j<(image_png.get_height()+70);++j){

                                 if(k<image_png.get_width()){

                                     png::rgb_pixel pixel=image_png.get_pixel(k,j-70);

                                     full_image.set_pixel(k,j,pixel);

                                 }

                                 else{

                                     size_t pos=k-w;

                                     png::rgb_pixel pixel=image_png.get_pixel(pos,j-70);

                                     full_image.set_pixel(k,j,pixel);

                                 }
                      }
                  }
        }

        full_image.write(file_out);

        std::cout<<"Image created.\n";

        break;
    }

    default:{

       std::cout<<"Error\n";

       break;

    }

  }

}

