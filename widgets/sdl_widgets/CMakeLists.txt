file(GLOB SOURCES *.cpp)

add_library(lib_sdl_widgets ${SOURCES})

target_link_libraries(lib_sdl_widgets
    lib_QT
)
