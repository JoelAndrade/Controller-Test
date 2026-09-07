#include "widgets/menus/ps4_menu/ps4_menu.h"
#include "widgets/sdl_widgets/sdl_main_widget.h"

#include <QT_Util.h>
#include <iostream>

QMainWindow *window_ptr;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    QMainWindow window;
    window_ptr = &window;
    QStackedWidget *stack_w = new QStackedWidget(&window);
    window.setWindowTitle("Controller Test");
    window.resize(1000, 700);
    
    // Create main menu
    QWidget *main_menu = new QWidget;
    QPushButton *ps4_button    = new QPushButton("PS4", main_menu);
    QPushButton *xbox_button   = new QPushButton("Xbox", main_menu);
    QPushButton *switch_button = new QPushButton("Switch", main_menu);
    ps4_button->setMaximumHeight(100);
    xbox_button->setMaximumHeight(100);
    switch_button->setMaximumHeight(100);
    
    // set up layout for main menu
    QVBoxLayout *main_menu_layout = new QVBoxLayout(main_menu);
    main_menu_layout->addWidget(ps4_button);
    main_menu_layout->addWidget(xbox_button);
    main_menu_layout->addWidget(switch_button);

    // Setup ps4 menu
    PS4Test *ps4_test = new PS4Test(stack_w, main_menu);
    QObject::connect(ps4_button, &QPushButton::clicked, [stack_w, ps4_test]() {
        stack_w->setCurrentWidget(ps4_test);
    });

    // Setup Xbox menu
    QObject::connect(xbox_button, &QPushButton::clicked, []() {
        std::cout << "Pressed Xbox Button" << std::endl;
    });

    // Setup Switch menu
    QObject::connect(switch_button, &QPushButton::clicked, []() {
        std::cout << "Pressed switch Button" << std::endl;
    });
    
    // Setup sdl widgets
    SDLWindow *sdl_window = new SDLWindow(stack_w, ps4_test);

    // Add all menus to stack_w
    stack_w->addWidget(main_menu);
    stack_w->addWidget(ps4_test);
    stack_w->addWidget(sdl_window);
    
    // Final setup for window
    window.setCentralWidget(stack_w);
    window.show();

    return app.exec();
}
