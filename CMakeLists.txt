cmake_minimum_required(VERSION 3.30)

project(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(ps4_menu)
add_subdirectory(SDL2-Utilites)
add_subdirectory(QT-Utilites)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(main main.cpp)

target_link_libraries(main
    lib_ps4_menu
    lib_SDL2
    lib_QT
    mingw32
)
