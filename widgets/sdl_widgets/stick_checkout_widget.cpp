#include "stick_checkout_widget.h"

#include <QT_Util.h>
#include <iostream>
#include <windows.h>

StickCheckoutW::StickCheckoutW(QStackedWidget *stack_w, QWidget *parent) : QWidget(parent)
{
    this->parent = parent;
    this->stack_w = stack_w;

    resize(1000, 700);

    sdl_process = new QProcess(this);

    connect(sdl_process, &QProcess::started, this, [this]() { qDebug() << "SDL process started"; });
    connect(sdl_process, &QProcess::finished, this, [this]() { qDebug() << "SDL process finished"; });
}

void StickCheckoutW::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    // Put resizing code here if nessary

    send_resize();
}

void StickCheckoutW::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        sdl_process->kill();
        stack_w->setCurrentWidget(parent);
    }

    QWidget::keyPressEvent(event);
}

void StickCheckoutW::showEvent(QShowEvent *event)
{
    if (sdl_process->state() != QProcess::Running)
    {
        start_SDL();
    }

    QWidget::showEvent(event);
    
    // Widget has been made visible
    qDebug() << "Widget shown";
}

void StickCheckoutW::start_SDL()
{
    HWND hwnd = (HWND)(this->winId());

    // Convert HWND to a string.
    quintptr hwnd_value = (quintptr)hwnd;
    QString hwnd_string = QString::number(hwnd_value);

    // Start the SDL executable.
    sdl_process->start("tests/bin/stick_checkout.exe", { "--extern", hwnd_string});
}

void StickCheckoutW::send_resize()
{
    if (!sdl_process || (sdl_process->state() != QProcess::Running))
        return;

    int width = this->width();
    int height = this->height();

    std::cout << "resize" << std::endl;

    // In a production application I'd use
    // a pipe/socket/shared memory mechanism
    // rather than trying to communicate through
    // command line arguments after startup.
    Q_UNUSED(width);
    Q_UNUSED(height);
}

