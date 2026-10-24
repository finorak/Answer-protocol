#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "common.h"
#include "Window.hpp"
#include "Server.hpp"
#include <memory>

int	sock;

void cleanup()
{
	TTF_Quit();
    SDL_Quit();
}

int init_renderer()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Erreur SDL : %s\n", SDL_GetError());
        return 0;
    }
	if (TTF_Init() == -1)
	{
		printf("Erreur SDL_ttf : %s\n", TTF_GetError());
		return 0;
	}
    return 1;
}


int main(int argc, char **argv)
{
    if (argc != 2)
	{
		printf("Please use the format ./client <server-ip-addr>\n");
		return (1);
	}
    if (!init_renderer())
        return (1);
    auto server = std::make_unique<Server>(argv[1]);
    if (!server->connected)
    {
        cleanup();
        return (1);
    }
    {
        Window window(1800, 900, server.get());
        window.run();
    }
    server.reset();
    cleanup();
    return (0);
}
