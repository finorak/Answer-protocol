// Copyright 2026 mrazakam

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <cstdio>
#include <memory>

#include "gui/Server.hpp"
#include "gui/Window.hpp"
#include "gui/common.h"

void cleanup() {
  TTF_Quit();
  SDL_Quit();
}

int init_renderer() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::printf("Erreur SDL : %s\n", SDL_GetError());
    return 0;
  }
  if (TTF_Init() == -1) {
    std::printf("Erreur SDL_ttf : %s\n", TTF_GetError());
    return 0;
  }
  return 1;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    std::printf("Please use the format ./client <server-ip-addr>\n");
    return 1;
  }
  if (!init_renderer()) {
    return (1);
  }
  auto server = std::make_unique<Server>(argv[1]);
  if (!server->connected) {
    cleanup();
    return 1;
  }
  {
    Window window(1800, 900, server.get());
    window.run();
  }
  server.reset();
  cleanup();
  return (0);
}
