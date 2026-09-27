
#include <SDL2/SDL.h>
#include <SDL_CLasses.h>
#include <SDL_Util.h>

#include <iostream>
#include <string>
#include <cstdint>
#include <cmath>

#include <windows.h>

#define PULLING_RATE (250)
#define MAX_JOY_VAL (32767.0)

#define LEFT_RECT_X (window.w/4)
#define LEFT_RECT_Y (window.h/2)
#define RIGHT_RECT_X (3*window.w/4)
#define RIGHT_RECT_Y (window.h/2)

bool run_external = true;
Window window;

int radius = 220;

static void run_stick_checkout(void);
static int map_stick_input_to_screen_pos(double raw_val, int center_pos);

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

    if (run_external)
    {
        //SDL_CreateWindowFrom() wraps an existing native window. SDL does NOT create the HWND itself here.
        window.init_external(hwnd);
    }
    else
    {
        SDL_DestroyWindow(window.window);
        
        window.init(1000, 700, "Stick Checkout", (SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN));
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

    run_stick_checkout();

    SDL_DestroyRenderer(window.renderer);
    SDL_DestroyWindow(window.window);
    SDL_Quit();

    return 0;
}

static void run_stick_checkout(void)
{
    Uint32 starting_tick;
    SDL_Event event;
        
    bool run = true;
    
    SDL_Joystick *ps4_controller = NULL;

    SDL_Rect left_containter_rect;
    left_containter_rect.x = LEFT_RECT_X;
    left_containter_rect.y = LEFT_RECT_Y;
    left_containter_rect.w = 2*radius + 1;
    left_containter_rect.h = 2*radius + 1;
    rect_make_dimensions(&left_containter_rect);
    rect_shiftXY(&left_containter_rect);

    SDL_Rect right_containter_rect;
    right_containter_rect.x = RIGHT_RECT_X;
    right_containter_rect.y = RIGHT_RECT_Y;
    right_containter_rect.w = 2*radius + 1;
    right_containter_rect.h = 2*radius + 1;
    rect_make_dimensions(&right_containter_rect);
    rect_shiftXY(&right_containter_rect);

    SDL_Rect left_point_rect;
    left_point_rect.x = LEFT_RECT_X;
    left_point_rect.y = LEFT_RECT_Y;
    left_point_rect.w = 5;
    left_point_rect.h = 5;
    rect_make_dimensions(&left_point_rect);
    rect_shiftXY(&left_point_rect);

    SDL_Rect right_point_rect;
    right_point_rect.x = RIGHT_RECT_X;
    right_point_rect.y = RIGHT_RECT_Y;
    right_point_rect.w = 5;
    right_point_rect.h = 5;
    rect_make_dimensions(&right_point_rect);
    rect_shiftXY(&right_point_rect);

    if (SDL_NumJoysticks() < 1)
    {
        return;
    }
    else
    {
        ps4_controller = SDL_JoystickOpen(0);
    }
    
    while (run)
    {
        starting_tick = SDL_GetTicks();

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                run = false;
                break;
            }

            if (event.type == SDL_WINDOWEVENT)
            {
                if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                {
                    run = false;
                    break;
                }
            }

            if (event.type == SDL_JOYAXISMOTION)
            {
                if (event.jaxis.axis == SDL_CONTROLLER_AXIS_LEFTX)
                {
                    left_point_rect.x = map_stick_input_to_screen_pos(event.jaxis.value, LEFT_RECT_X);
                    rect_make_dimensions(&left_point_rect);
                    rect_shiftX(&left_point_rect);

                    // std::cout << "x: " << event.jaxis.value << std::endl;
                }
                else if (event.jaxis.axis == SDL_CONTROLLER_AXIS_LEFTY)
                {
                    left_point_rect.y = map_stick_input_to_screen_pos(event.jaxis.value, LEFT_RECT_Y);
                    rect_make_dimensions(&left_point_rect);
                    rect_shiftY(&left_point_rect);
                    // std::cout << "y: " << event.jaxis.value << std::endl;
                }
                else if (event.jaxis.axis == SDL_CONTROLLER_AXIS_RIGHTX)
                {
                    right_point_rect.x = map_stick_input_to_screen_pos(event.jaxis.value, RIGHT_RECT_X);
                    rect_make_dimensions(&right_point_rect);
                    rect_shiftX(&right_point_rect);

                    // std::cout << "x: " << event.jaxis.value << std::endl;
                }
                else if (event.jaxis.axis == SDL_CONTROLLER_AXIS_RIGHTY)
                {
                    right_point_rect.y = map_stick_input_to_screen_pos(event.jaxis.value, RIGHT_RECT_Y);
                    rect_make_dimensions(&right_point_rect);
                    rect_shiftY(&right_point_rect);
                    
                    // std::cout << "y: " << event.jaxis.value << std::endl;
                }
            }
        }

        window.get_window_size();
        window.clear_render();
        
        window.draw_line(LEFT_RECT_X - radius, LEFT_RECT_Y,
                         LEFT_RECT_X + radius, LEFT_RECT_Y,
                        SDL_Color{0, 255, 0, 255}, 2, 2);

        window.draw_line(LEFT_RECT_X, LEFT_RECT_Y - radius,
                         LEFT_RECT_X, LEFT_RECT_Y + radius,
                        SDL_Color{0, 255, 0, 255}, 2, 2);


        window.draw_line(RIGHT_RECT_X - radius, RIGHT_RECT_Y,
                         RIGHT_RECT_X + radius, RIGHT_RECT_Y,
                        SDL_Color{0, 255, 0, 255}, 2, 2);

        window.draw_line(RIGHT_RECT_X, RIGHT_RECT_Y - radius,
                         RIGHT_RECT_X, RIGHT_RECT_Y + radius,
                        SDL_Color{0, 255, 0, 255}, 2, 2);
                        

        window.draw_rect(SDL_Color{0, 250, 250, 255}, left_containter_rect, 2, 2);
        window.draw_rect(SDL_Color{0, 250, 250, 255}, right_containter_rect, 2, 2);

        window.fill_rect(SDL_Color{255, 0, 255, 255}, left_point_rect, 1, 1);
        window.fill_rect(SDL_Color{255, 0, 255, 255}, right_point_rect, 1, 1);
        
        window.render();

        frame_cap(PULLING_RATE, starting_tick);
    }
}

static int map_stick_input_to_screen_pos(double raw_val, int center_pos)
{
    return std::round((double)radius * ((raw_val)/MAX_JOY_VAL)) + center_pos;
}
