cmake_minimum_required(VERSION 3.8 FATAL_ERROR)


project(final_project_v1)

add_executable(${PROJECT_NAME}
 "main.cpp"
 )
add_executable(${NAMESPACE}::${COMPONENT} ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

include(FindPkgConfig)
pkg_check_modules(POPPLER REQUIRED IMPORTED_TARGET poppler-cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::POPPLER)

include(FindPkgConfig)
pkg_check_modules(lib REQUIRED IMPORTED_TARGET libpng)
target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::lib)

find_package(PNG REQUIRED)

include(FindPackageHandleStandardArgs)

find_path(png++_INCLUDE_DIR
    NAMES
        png++/color.hpp
        png++/config.hpp
        png++/consumer.hpp
        png++/convert_color_space.hpp
        png++/end_info.hpp
        png++/error.hpp
        png++/ga_pixel.hpp
        png++/generator.hpp
        png++/gray_pixel.hpp
        png++/image.hpp
        png++/image_info.hpp
        png++/index_pixel.hpp
        png++/info.hpp
        png++/info_base.hpp
        png++/io_base.hpp
        png++/packed_pixel.hpp
        png++/palette.hpp
        png++/pixel_buffer.hpp
        png++/pixel_traits.hpp
        png++/png.hpp
        png++/reader.hpp
        png++/require_color_space.hpp
        png++/rgb_pixel.hpp
        png++/rgba_pixel.hpp
        png++/streaming_base.hpp
        png++/tRNS.hpp
        png++/types.hpp
        png++/writer.hpp
        )
    if(png++_FOUND AND NOT TARGET png++::png++)
        add_library(png++:png++ INTERFACE IMPORTED)
        set_target_properties(png++::png++ PROPERTIES
            IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
            INTERFACE_INCLUDE_DIRECTORIES "${png++_INCLUDE_DIR}")
    endif()
    mark_as_advanced(png++_INCLUDE_DIR)
#set(png++_INCLUDE_DIRS ${png++_INCLUDE_DIR} ${PNG_INCLUDE_DIRS})
#set(png++_LIBRARIES ${PNG_LIBRARIES})

#find_package_handle_standard_args(png++ DEFAULT_MSG
 #   png++_INCLUDE_DIR)

#if(png++_FOUND)
  #  set(png++_INCLUDE_DIRS ${png++_INCLUDE_DIR})
  #  set(png++_LIBRARIES ${png++_LIBRARY})
#endif()









