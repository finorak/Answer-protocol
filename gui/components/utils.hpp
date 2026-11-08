#ifndef COMPONENTS_UTILS_HPP
#define COMPONENTS_UTILS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

void drawFilledRoundedRect(
    SDL_Renderer* renderer,
    SDL_Rect& rect,
    int radius,
    SDL_Color color
);
void drawRoundedBorder(
    SDL_Renderer* renderer,
    SDL_Rect& rect,
    int radius,
    SDL_Color color
);
int countUtf8Characters(const std::string &text);
int measureTextWidth(TTF_Font *font, const std::string &text,
    int letter_spacing = 0);
void renderText(SDL_Renderer *renderer, TTF_Font *font,
    const std::string &text, int x, int y, SDL_Color color,
    int letter_spacing = 0);

#endif
