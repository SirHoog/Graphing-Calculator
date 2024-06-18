#pragma once

#include <SDL2/SDL.h>

// _O => _Overrides

int SDL_SetRenderDrawColor_O(SDL_Renderer *renderer, SDL_Color color)
{
  return SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
};