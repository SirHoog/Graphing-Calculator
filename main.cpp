#include <stdio.h>
#include <array>
#include <SDL2/SDL.h>

const char* TITLE = "Graphing Calculator";
const int WIDTH = 900, HEIGHT = 900;
const SDL_Color BG_COLOR = (SDL_Color){0, 0, 0, 0};

int WinMain(int argc, char *argv[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL_Init failed: %s\n", SDL_GetError());

        return 1;
    };

    window = SDL_CreateWindow(
        TITLE,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH, HEIGHT,
        SDL_WINDOW_ALLOW_HIGHDPI
    );
    
    if (window == NULL)
    {
        printf("Could not create window: %s\n", SDL_GetError());

        return 1;
    };

    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, BG_COLOR.a);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Event event;

    while (true)
    {
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                break;
            }
        }
    };

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}