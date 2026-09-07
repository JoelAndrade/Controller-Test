#include <QT_Util.h>
#include <iostream>
#include <windows.h>

#ifndef SDL_MAIN_WIDGET_H
#define SDL_MAIN_WIDGET_H

class SDLWindow : public QWidget
{
public:
    SDLWindow(QStackedWidget *stack_w, QWidget *parent = nullptr);


protected:
void resizeEvent(QResizeEvent *event) override;

private:
    QProcess *sdlProcess = nullptr;

    void startSDL(void);
    void sendResize(void);
};

#endif // SDL_MAIN_WIDGET_H