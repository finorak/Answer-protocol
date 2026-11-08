#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>
#include "Server.hpp"

class Window
{
    public:
        int width;
        int height;
        Server *server;
        SDL_Window *window;
        SDL_Renderer *renderer; 

        Window(int width, int height, Server *server);
        void run();
        ~Window();

};


#endif