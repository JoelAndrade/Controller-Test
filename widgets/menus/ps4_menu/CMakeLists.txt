file(GLOB SOURCES *.cpp)

add_library(lib_ps4_menu ${SOURCES})

target_link_libraries(lib_ps4_menu
    lib_QT
)
