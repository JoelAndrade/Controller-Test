#include "sdl_main_widget.h"

#include <QT_Util.h>
#include <iostream>
#include <windows.h>

SDLWindow::SDLWindow(QStackedWidget *stack_w, QWidget *parent) : QWidget(parent)
{
    resize(1000, 700);

    // Make sure the HWND exists.
    this->setAttribute(Qt::WA_NativeWindow);
    this->winId();

    startSDL();
}

void SDLWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    // Put resizing code here if nessary

    sendResize();
}

void SDLWindow::startSDL()
{
    HWND hwnd = (HWND)(this->winId());

    // Convert HWND to a string.
    quintptr hwndValue = (quintptr)hwnd;
    QString hwndString = QString::number(hwndValue);

    sdlProcess = new QProcess(this);

    // Start the SDL executable.
    sdlProcess->start( "tests/bin/sdl_main.exe", { "--extern", hwndString});

    connect(sdlProcess, &QProcess::started, this, [this]() { qDebug() << "SDL process started"; });
    connect( sdlProcess, &QProcess::finished, this, [this]() { qDebug() << "SDL process finished"; });
}

void SDLWindow::sendResize()
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

