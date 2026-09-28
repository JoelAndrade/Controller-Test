
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

    // Find --extern argument.
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

    SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1"); // Allow background joy stick inputs

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
    
    SDL_GameController *ps4_controller = NULL;

    SDL_Rect left_containter_rect;
    left_containter_rect.w = 2*radius + 1;
    left_containter_rect.h = 2*radius + 1;

    SDL_Rect right_containter_rect;
    right_containter_rect.w = 2*radius + 1;
    right_containter_rect.h = 2*radius + 1;

    SDL_Rect left_point_rect;
    left_point_rect.w = 5;
    left_point_rect.h = 5;

    SDL_Rect right_point_rect;
    right_point_rect.w = 5;
    right_point_rect.h = 5;

    bool left_detect_x = false;
    bool left_detect_y = false;
    bool right_detect_x = false;
    bool right_detect_y = false;

    if (SDL_NumJoysticks() < 1)
    {
        return;
    }
    else
    {
        ps4_controller = SDL_GameControllerOpen(0);
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
                    left_detect_x = true;
                }
                else if (event.jaxis.axis == SDL_CONTROLLER_AXIS_LEFTY)
                {
                    left_point_rect.y = map_stick_input_to_screen_pos(event.jaxis.value, LEFT_RECT_Y);
                    rect_make_dimensions(&left_point_rect);
                    rect_shiftY(&left_point_rect);
                    left_detect_y = true;
                }
                else if (event.jaxis.axis == SDL_CONTROLLER_AXIS_RIGHTX)
                {
                    right_point_rect.x = map_stick_input_to_screen_pos(event.jaxis.value, RIGHT_RECT_X);
                    rect_make_dimensions(&right_point_rect);
                    rect_shiftX(&right_point_rect);
                    right_detect_x = true;
                }
                else if (event.jaxis.axis == SDL_CONTROLLER_AXIS_RIGHTY)
                {
                    right_point_rect.y = map_stick_input_to_screen_pos(event.jaxis.value, RIGHT_RECT_Y);
                    rect_make_dimensions(&right_point_rect);
                    rect_shiftY(&right_point_rect);
                    right_detect_y = true;
                }
            }
        }

        window.get_window_size();

        left_containter_rect.x = LEFT_RECT_X;
        left_containter_rect.y = LEFT_RECT_Y;
        rect_make_dimensions(&left_containter_rect);
        rect_shiftXY(&left_containter_rect);

        right_containter_rect.x = RIGHT_RECT_X;
        right_containter_rect.y = RIGHT_RECT_Y;
        rect_make_dimensions(&right_containter_rect);
        rect_shiftXY(&right_containter_rect);

        window.clear_render();
        
        // Draw the the box cross
        window.draw_line(LEFT_RECT_X - radius, LEFT_RECT_Y,
                         LEFT_RECT_X + radius, LEFT_RECT_Y,
                         SDL_green, 2, 2);

        window.draw_line(LEFT_RECT_X, LEFT_RECT_Y - radius,
                         LEFT_RECT_X, LEFT_RECT_Y + radius,
                         SDL_green, 2, 2);

        window.draw_line(RIGHT_RECT_X - radius, RIGHT_RECT_Y,
                         RIGHT_RECT_X + radius, RIGHT_RECT_Y,
                         SDL_green, 2, 2);

        window.draw_line(RIGHT_RECT_X, RIGHT_RECT_Y - radius,
                         RIGHT_RECT_X, RIGHT_RECT_Y + radius,
                         SDL_green, 2, 2);

        // draw containers
        window.draw_rect(SDL_cyan, left_containter_rect, 2, 2);
        window.draw_rect(SDL_cyan, right_containter_rect, 2, 2);

        // draw the points
        if (left_detect_x && left_detect_y)
        {
            window.fill_rect(SDL_violet, left_point_rect, 1, 1);
        }
        if (right_detect_x && right_detect_y)
        {
            window.fill_rect(SDL_violet, right_point_rect, 1, 1);
        }

        window.render();

        frame_cap(PULLING_RATE, starting_tick);
    }
}

static int map_stick_input_to_screen_pos(double raw_val, int center_pos)
{
    return std::round((double)radius * ((raw_val)/MAX_JOY_VAL)) + center_pos;
}
