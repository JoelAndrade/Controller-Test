#include "ps4_menu.h"

#include <QT_Util.h>
#include <iostream>

PS4Test::PS4Test(QStackedWidget *stack_w, QWidget *parent) : QWidget(parent)
{
    this->parent = parent;
    this->stack_w = stack_w;
    
    // Create buttons
    QPushButton *stick_checkout = new QPushButton("Stick Checkout", this);
    QPushButton *trigger_checkout = new QPushButton("Trigger Checkout", this);
    QPushButton *exit = new QPushButton("Exit", this);
    stick_checkout->setMaximumHeight(100);
    trigger_checkout->setMaximumHeight(100);
    exit->setMaximumHeight(100);
    
    connect(stick_checkout, &QPushButton::clicked, this, &PS4Test::stick_checkout_pressed);
    connect(trigger_checkout, &QPushButton::clicked, this, &PS4Test::trigger_checkout_pressed);
    connect(exit, &QPushButton::clicked, this, &PS4Test::exit_pressed);
    
    // Add to main layout
    QVBoxLayout *main_layout = new QVBoxLayout(this);
    main_layout->addWidget(stick_checkout);
    main_layout->addWidget(trigger_checkout);
    main_layout->addWidget(exit);
}

void PS4Test::stick_checkout_pressed(void)
{
    stack_w->setCurrentIndex(2);
}

void PS4Test::trigger_checkout_pressed(void)
{
    std::cout << "Pressed trigger checkout" << std::endl;
}

void PS4Test::exit_pressed(void)
{
    stack_w->setCurrentWidget(parent);
}
