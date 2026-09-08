#include <QT_Util.h>
#include <iostream>

#ifndef PS4_MENU_H
#define PS4_MENU_H

class PS4Test : public QWidget
{
public:
    QWidget *stick_child;
    QWidget *trigger_child;

    PS4Test(QStackedWidget *stack_w, QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QWidget *parent;
    QStackedWidget *stack_w;

    void stick_checkout_pressed(void);
    void trigger_checkout_pressed(void);
    void exit_pressed(void);
};

#endif // PS4_MENU_H
