
#include <SDL2/SDL.h>
#include <SDL_CLasses.h>
#include <SDL_Util.h>

#include <iostream>
#include <string>
#include <cstdint>

#include <windows.h>

#define FPS (500)

bool run_external = true;

int main(int argc, char *argv[])
{
    HWND hwnd = nullptr;

    // Find --parent argument.
    for (int i = 1; i < argc; ++i)
    {
        if ((std::string(argv[i]) == "--extern") && (argc > i + 1))
        {
            uintptr_t value = (uintptr_t)(std::stoull(argv[i + 1]));
            hwnd = (HWND)value;

            break;
        }
    }

    if (!hwnd)
    {
        std::cout << "No parent HWND supplied\n";
        
        run_external = false;
    }

    // Initialize SDL.
    SDL_Init(SDL_INIT_EVERYTHING);

    Window window;
    if (run_external)
    {
        //SDL_CreateWindowFrom() wraps an existing native window. SDL does NOT create the HWND itself here.
        window.init_external(hwnd);
    }
    else
    {
        SDL_DestroyWindow(window.window);
        
        window.init(840, 280, "Stick Checkout", (SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN));
    }

    if (!window.window)
    {
        std::cerr << "SDL_CreateWindowFrom failed: " << SDL_GetError() << "\n";

        SDL_Quit();

        return 1;
    }

    if (!window.renderer)
    {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << "\n";

        SDL_DestroyWindow(window.window);
        SDL_Quit();

        return 1;
    }

    Uint32 starting_tick;
    SDL_Event event;

    while (true)
    {
        starting_tick = SDL_GetTicks();

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                break;
            }

            if (event.type == SDL_WINDOWEVENT)
            {
                if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                {
                    break;
                }
            }
        }


        window.get_window_size();
        window.clear_render();

        SDL_Rect rect;
        rect.x = window.w / 2 - 100;
        rect.y = window.h / 2 - 75;
        rect.w = 200;
        rect.h = 150;

        window.fill_rect(SDL_Color{220, 50, 50, 255}, rect, 1, 1);

        window.render();

        frame_cap(FPS, starting_tick);
    }

    SDL_DestroyRenderer(window.renderer);
    SDL_DestroyWindow(window.window);
    SDL_Quit();

    return 0;
}