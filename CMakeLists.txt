cmake_minimum_required(VERSION 3.30)

project(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(SDL2-Utilites)
add_subdirectory(QT-Utilites)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(main main.cpp)

# target_include_directories(main PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}/include
#     ${CMAKE_CURRENT_SOURCE_DIR}/include/QtWidgets
# )
    
# target_link_directories(main PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}/lib
# )

target_link_libraries(main
    lib_SDL2
    lib_QT
)

target_link_libraries(main
    mingw32
    # Qt6Widgets
    # Qt6Gui
    # Qt6Core
)
