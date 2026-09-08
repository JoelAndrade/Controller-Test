#include "stick_checkout_widget.h"

#include <QT_Util.h>
#include <iostream>
#include <windows.h>

StickCheckoutW::StickCheckoutW(QStackedWidget *stack_w, QWidget *parent) : QWidget(parent)
{
    this->parent = parent;
    this->stack_w = stack_w;

    resize(1000, 700);

    // Make sure the HWND exists.
    this->setAttribute(Qt::WA_NativeWindow);
    this->winId();

    startSDL();
}

void StickCheckoutW::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    // Put resizing code here if nessary

    sendResize();
}

void StickCheckoutW::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        stack_w->setCurrentWidget(parent);
    }

    QWidget::keyPressEvent(event);
}

void StickCheckoutW::startSDL()
{
    HWND hwnd = (HWND)(this->winId());

    // Convert HWND to a string.
    quintptr hwndValue = (quintptr)hwnd;
    QString hwndString = QString::number(hwndValue);

    sdlProcess = new QProcess(this);

    // Start the SDL executable.
    sdlProcess->start( "tests/bin/stick_checkout.exe", { "--extern", hwndString});

    connect(sdlProcess, &QProcess::started, this, [this]() { qDebug() << "SDL process started"; });
    connect( sdlProcess, &QProcess::finished, this, [this]() { qDebug() << "SDL process finished"; });
}

void StickCheckoutW::sendResize()
{
    if (!sdlProcess || (sdlProcess->state() != QProcess::Running))
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

