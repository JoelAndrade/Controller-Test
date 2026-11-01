#include <QT_Util.h>
#include <iostream>
#include <windows.h>

#ifndef BUTTON_CHECKOUT_W_H
#define BUTTON_CHECKOUT_W_H

class ButtonCheckoutW : public QWidget
{
public:
    ButtonCheckoutW(QStackedWidget *stack_w, QWidget *parent = nullptr);


protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event);
    void showEvent(QShowEvent *event);

private:
    QWidget *parent;
    QProcess *sdl_process;
    QStackedWidget *stack_w;

    void start_SDL(void);
    void send_resize(void);
};

#endif // BUTTON_CHECKOUT_W_H