file(GLOB SOURCES *.cpp)

add_library(lib_stick_checkout_w ${SOURCES})

target_link_libraries(lib_stick_checkout_w
    lib_QT
)
