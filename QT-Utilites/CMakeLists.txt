add_library(lib_QT INTERFACE)

target_include_directories(lib_QT INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/QtWidgets
)

target_link_directories(lib_QT INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

target_link_libraries(lib_QT INTERFACE
    Qt6Widgets
    Qt6Gui
    Qt6Core
)
