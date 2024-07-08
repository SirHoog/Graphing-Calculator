#include <stdio.h>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2_Overrides.h>

/*TODO:
* Graph a function ✅
* Graph a grid behind it ✅
* Aspect ratio stuff (dynamic window sizing)
* Add zoom (not the meeting app XD)
* Add panning
* Add dynamic screen size

Challenges:
* Add an imgui menu for at-runtime customization
* Write an interpreter for math functions using user input fom the imgui menu (like an `eval` function in Python)
* Graph multiple functions
* Add a time variable that allows the user to render any function real time
* Add variable sliders
* Literally recreate desmos (kinda a joke)
*/

const char *TITLE = "Graphing Calculator";
const int SCREEN_HEIGHT = 900, SCREEN_WIDTH = 1280;
const SDL_Color BG_COLOR = (SDL_Color){0, 0, 0, 0};
const SDL_Color GRID_COLOR = (SDL_Color){66, 135, 245, 64};
const SDL_Color GRAPH_COLOR = (SDL_Color){255, 255, 255, 255};
const int GRID_CELL_SIZE = 50;
const int dx = 3; // How many pixels between each x inputted into the graph function. It's technically delta x, but I don't care. I'm going to use it because it's shorter.
// const float zoom = 1;
std::vector<SDL_Point> graphPoints = {};

float GraphFunction(float x)
{
    return sin(pow(x / 100, 2)) * 100;
};

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
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_ALLOW_HIGHDPI
    );
    
    if (window == NULL)
    {
        printf("Could not create window: %s\n", SDL_GetError());

        return 1;
    };

    renderer = SDL_CreateRenderer(window, -1, 0);
    
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor_O(renderer, BG_COLOR);
    SDL_RenderClear(renderer);
    
    // Render Grid

    SDL_SetRenderDrawColor_O(renderer, GRID_COLOR);

    for (int i = -SCREEN_WIDTH / 2; i < SCREEN_WIDTH / 2; i += GRID_CELL_SIZE)
    {
        for (int j = -SCREEN_HEIGHT / 2; j < SCREEN_HEIGHT / 2; j += GRID_CELL_SIZE)
        {
            const SDL_Rect gridCellRect = (SDL_Rect){i + SCREEN_WIDTH / 2, j + SCREEN_HEIGHT / 2, GRID_CELL_SIZE, GRID_CELL_SIZE};

            SDL_RenderDrawRect(renderer, &gridCellRect);
        }
    };

    // Render Graph
    SDL_SetRenderDrawColor_O(renderer, GRAPH_COLOR);

    for (int i = -SCREEN_WIDTH / 2; i < SCREEN_WIDTH / 2; i += dx)
    {
        graphPoints.push_back((SDL_Point){i + SCREEN_WIDTH / 2, int(-GraphFunction(i)) + SCREEN_HEIGHT / 2});
    };

    const SDL_Point *points = &graphPoints[0]; // https://stackoverflow.com/questions/2923272/how-to-convert-vector-to-array

    SDL_RenderDrawLines(renderer, points, graphPoints.size());

    SDL_RenderPresent(renderer); // Render one function once

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
};