
#include <SDL2/SDL.h>
#include <SDL_Util.h>

#include <iostream>
#include <string>
#include <cstdint>

#include <windows.h>

bool run_external = true;

int main(int argc, char *argv[])
{
    HWND parentHwnd = nullptr;

    // Find --parent argument.
    for (int i = 1; i < argc; ++i)
    {
        if ((std::string(argv[i]) == "--extern") && (argc > i + 1))
        {
            uintptr_t value = (uintptr_t)(std::stoull(argv[i + 1]));
            parentHwnd = (HWND)value;

            break;
        }
    }

    if (!parentHwnd)
    {
        std::cout << "No parent HWND supplied\n";
        
        run_external = false;
    }

    // Initialize SDL.
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window;
    if (run_external)
    {
        /*
         * SDL_CreateWindowFrom() wraps an existing
         * native window.
         *
         * SDL does NOT create the HWND itself here.
         */
        window = SDL_CreateWindowFrom((void *)parentHwnd);
    }
    else
    {
        SDL_DestroyWindow(window);

        window = SDL_CreateWindow("test sdl screen", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, (SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN));
    }

    if (!window)
    {
        std::cerr << "SDL_CreateWindowFrom failed: " << SDL_GetError() << "\n";

        SDL_Quit();

        return 1;
    }

    // Create renderer.
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << "\n";

        SDL_DestroyWindow(window);
        SDL_Quit();

        return 1;
    }


    bool running = true;

    while (running)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }

            if (event.type == SDL_WINDOWEVENT)
            {
                if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                {
                    running = false;
                }
            }
        }

        // Get current size.
        int width;
        int height;

        SDL_GetWindowSize(window, &width, &height);

        // Render background.
        SDL_SetRenderDrawColor(renderer, 30, 30, 40, 255); // Dark background

        SDL_RenderClear(renderer);

        // Draw red rectangle.
        SDL_SetRenderDrawColor(renderer, 220, 50, 50, 255);

        // SDL_Rect rect;
        // rect.x = 0;
        // rect.y = 0;
        // rect.w = 20;
        // rect.h = 15;
        // rect_make_dimensions(&rect);
        // rect_shiftXY(&rect);

        SDL_Rect rect;
        rect.x = width / 2 - 100;
        rect.y = height / 2 - 75;
        rect.w = 200;
        rect.h = 150;

        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}