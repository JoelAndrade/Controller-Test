#include "ps4_menu/ps4_menu.h"

#include <QT_Util.h>
#include <iostream>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    QMainWindow window;
    QStackedWidget *stack_w = new QStackedWidget(&window);
    window.setWindowTitle("Controller Test");
    window.resize(300, 200);
    
    // Create main menu
    QWidget *main_menu = new QWidget;
    QPushButton *ps4_button    = new QPushButton("PS4", main_menu);
    QPushButton *xbox_button   = new QPushButton("Xbox", main_menu);
    QPushButton *switch_button = new QPushButton("Switch", main_menu);
    
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
    
    // Add all menus to stack_w
    stack_w->addWidget(main_menu);
    stack_w->addWidget(ps4_test);
    
    // Final setup for window
    window.setCentralWidget(stack_w);
    window.show();

    return app.exec();
}


// int main(int argc, char *argv[])
// {
//     QApplication app(argc, argv);

//     QMainWindow window;
//     window.setWindowTitle("Qt Menu Example");
//     window.resize(500, 300);

//     // Create the File menu
//     QMenu *fileMenu = window.menuBar()->addMenu("File");

//     // Create actions
//     QAction *newAction = new QAction("New", &window);
//     QAction *openAction = new QAction("Open", &window);
//     QAction *exitAction = new QAction("Exit", &window);

//     // Add actions to File menu
//     fileMenu->addAction(newAction);
//     fileMenu->addAction(openAction);
//     fileMenu->addSeparator();
//     fileMenu->addAction(exitAction);

//     // Exit when Exit is clicked
//     QObject::connect(exitAction, &QAction::triggered, &app, &QApplication::quit);

//     window.show();

//     return app.exec();
// }

// int main(int argc, char *argv[])
// {
//     QApplication app(argc, argv);

//     QWidget window;
//     window.setWindowTitle("Multiple Buttons");
//     window.resize(300, 200);

//     QPushButton *button1 = new QPushButton("PS4");
//     QPushButton *button2 = new QPushButton("XBox");
//     QPushButton *button3 = new QPushButton("Switch");
    
//     QVBoxLayout *layout = new QVBoxLayout(&window); // Lines up the buttons for you
//     layout->addWidget(button1);
//     layout->addWidget(button2);
//     layout->addWidget(button3);

//     window.show();

//     return app.exec();
// }





// class ControllerTest : public QWidget
// {
//     public:
//         ControllerTest(QWidget *parent = nullptr) : QWidget(parent)
//         {
//             setWindowTitle("Controller Test");
//             resize(300, 200);

//             // 1. Create main vertical layout and stacked widget wrapper
//             QVBoxLayout *mainLayout = new QVBoxLayout(this);
//             stackedWidget = new QStackedWidget(this);
//             mainLayout->addWidget(stackedWidget);

//             // 2. Setup the individual views
//             main_menu();
//             button_checkout();
//         }

//     private:
//         QStackedWidget *stackedWidget;

//         void main_menu(void)
//         {
//             QWidget *page = new QWidget();
            
//             QPushButton *ps4_button = new QPushButton("PS4", page);
//             QPushButton *xbox_button = new QPushButton("XBox", page);
//             QPushButton *switch_button = new QPushButton("Switch", page);

//             QVBoxLayout *layout = new QVBoxLayout(page);
//             layout->addWidget(ps4_button);
//             layout->addWidget(xbox_button);
//             layout->addWidget(switch_button);

//             // Switch to child menu (Index 1) when clicked
//             connect(ps4_button, &QPushButton::clicked, this, [this]() { stackedWidget->setCurrentIndex(1);});

//             stackedWidget->addWidget(page); // Index 0
//         }

//         void button_checkout(void)
//         {
//             QWidget *page = new QWidget();
//             QVBoxLayout *layout = new QVBoxLayout(page);

//             QLabel *label = new QLabel("Child Menu Screen", page);
//             QPushButton *btnBack = new QPushButton("Back to Main Menu", page);

//             layout->addWidget(label);
//             layout->addWidget(btnBack);

//             // Switch back to main menu (Index 0) when clicked
//             connect(btnBack, &QPushButton::clicked, this, [this]() {
//                 stackedWidget->setCurrentIndex(0);
//             });

//             stackedWidget->addWidget(page); // Index 1
//         }
// };

// int main(int argc, char *argv[])\
// {
//     QApplication app(argc, argv);
//     ControllerTest controller;
//     controller.show();
//     return app.exec();
// }




// int main(int argc, char *argv[]) {
//     QApplication app(argc, argv);

//     // 1. Create the main window
//     QWidget window;
//     window.setWindowTitle("Controller Test");
//     window.resize(300, 200);
    
    
//     // 2. Setup the layouts
//     QStackedWidget *stackedWidget = new QStackedWidget(&window);

//     QVBoxLayout *window_layout = new QVBoxLayout(&window);
//     window_layout->addWidget(stackedWidget);
    
//     // ==========================================
//     // PAGE 0: Main Menu
//     // ==========================================
//     QWidget *main_menu = new QWidget();
//     QPushButton *ps4_button    = new QPushButton("PS4", main_menu);
//     QPushButton *xbox_button   = new QPushButton("Xbox", main_menu);
//     QPushButton *switch_button = new QPushButton("Switch", main_menu);
    
//     QVBoxLayout *main_menu_layout = new QVBoxLayout(main_menu);
//     main_menu_layout->addWidget(ps4_button);
//     main_menu_layout->addWidget(xbox_button);
//     main_menu_layout->addWidget(switch_button);
//     stackedWidget->addWidget(main_menu); // Index 0
    
//     PS4Test ps4_test(main_menu, stackedWidget);
//     stackedWidget->addWidget(ps4_test.menu_page); // Index 1
    
//     // // ==========================================
//     // // PAGE 1: Child Menu
//     // // ==========================================
//     // QWidget *childMenuPage = new QWidget();
//     // QVBoxLayout *childMenuLayout = new QVBoxLayout(childMenuPage);

//     // QLabel *childLabel = new QLabel("Child Menu Screen", childMenuPage);
//     // QPushButton *btnBack = new QPushButton("Back to Main Menu", childMenuPage);

//     // childMenuLayout->addWidget(childLabel);
//     // childMenuLayout->addWidget(btnBack);
//     // stackedWidget->addWidget(childMenuPage); // Index 1

//     // // ==========================================
//     // // BUTTON CONNECTIONS (Lambda Expressions)
//     // // ==========================================
//     // // Capture 'stackedWidget' pointer by value [stackedWidget] to use it inside the lambdas
//     QObject::connect(ps4_button, &QPushButton::clicked, [stackedWidget]() {
//         stackedWidget->setCurrentIndex(1);
//     });

//     // QObject::connect(btnBack, &QPushButton::clicked, [stackedWidget]() {
//     //     stackedWidget->setCurrentIndex(0);
//     // });

//     // 3. Display the window and start the loop
//     window.show();
//     return app.exec();
// }








// int main(int argc, char *argv[])
// {
//     QApplication app(argc, argv);

//     QMainWindow window;
//     window.setWindowTitle("My Application");
//     window.resize(400, 300);

//     // Central widget
//     QWidget *centralWidget = new QWidget();
//     std::cout << "parent: " << centralWidget << std::endl;

//     QWidget *child = new QWidget(centralWidget);
//     std::cout << "child: " << child << std::endl;
//     std::cout << "parent call: " << child->parentWidget() << std::endl;
    


//     // Layout
//     QVBoxLayout *layout = new QVBoxLayout(centralWidget);

//     // Buttons
//     QPushButton *button1 = new QPushButton("Button 1");
//     QPushButton *button2 = new QPushButton("Button 2");
//     QPushButton *button3 = new QPushButton("Button 3");

//     // Add buttons to layout
//     layout->addWidget(button1);
//     layout->addWidget(button2);
//     layout->addWidget(button3);

//     // Set central widget
//     window.setCentralWidget(centralWidget);

//     window.show();

//     return app.exec();
// }