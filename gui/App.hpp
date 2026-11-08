#ifndef APP_HPP
#define APP_HPP

#include <SDL2/SDL.h>
#include <vector>

struct App
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<SDL_Event> events;
};

#endif