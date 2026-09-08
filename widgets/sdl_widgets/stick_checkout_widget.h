#include <QT_Util.h>
#include <iostream>
#include <windows.h>

#ifndef STICK_CHECKOUT_W_H
#define STICK_CHECKOUT_W_H

class StickCheckoutW : public QWidget
{
public:
    StickCheckoutW(QStackedWidget *stack_w, QWidget *parent = nullptr);


protected:
void resizeEvent(QResizeEvent *event) override;
void keyPressEvent(QKeyEvent *event);


private:
    QWidget *parent;
    QProcess *sdlProcess;
    QStackedWidget *stack_w;

    void startSDL(void);
    void sendResize(void);
};

#endif // STICK_CHECKOUT_W_H