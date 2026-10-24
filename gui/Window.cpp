#include <iostream>
#include <sys/socket.h>
#include "Window.hpp"
#include "App.hpp"
#include "components/basic/Text.hpp"
#include "components/basic/Input.hpp"
#include "components/basic/Button.hpp"
#include "components/basic/ProgressBar.hpp"
#include "components/page/Connect.hpp"
#include "components/page/TAPInterface.hpp"
#include "components/features/Environment.hpp"
#include "components/features/Header.hpp"
#include <vector>


using namespace std;

Window::Window(int width, int height, Server *server)
{
    this->width = width;
    this->height = height;
    this->server = server;

    this->window = SDL_CreateWindow(
        "The answer protocol",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );

    this->renderer = SDL_CreateRenderer(
        this->window,
        -1,
        SDL_RENDERER_ACCELERATED
    );
}


Window::~Window()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
}

void Window::run()
{
    int running = 1;
    SDL_Event event;
    bool connected = false;

    App app{
        this->window,
        this->renderer,
        {}
    };

    App *app_ptr = &app;

    TAPInterface tap_interface(app_ptr, this->width, this->height, server);

    Connect connect_page(app_ptr, this->width, this->height, server, [&connected, &tap_interface](string u) {
        connected = true;
        tap_interface.header->update_username(u);
        tap_interface.header->update_hp();
        tap_interface.environment->look();
    });

    SDL_StartTextInput();

    while (running)
    {
        app.events.clear();

        while (SDL_PollEvent(&event))
        {
            app.events.push_back(event);

            if (event.type == SDL_QUIT)
            {
                if (connected && server->connected)
                    send(server->sock, "QUIT\n", 5, MSG_NOSIGNAL);
                running = false;
            }
        }

        if (running)
            server->dispatch_events();

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        if (!connected)
            connect_page.render();
        else
            tap_interface.render();

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    SDL_StopTextInput();
}
