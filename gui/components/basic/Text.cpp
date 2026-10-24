#include "Text.hpp"
#include "../utils.hpp"
#include <iostream>

using namespace std;

Text::Text(
    App *app,
    int x,
    int y,
    string text,
    int size,
    SDL_Color color,
    int letter_spacing
)
    : Component(app, x, y)
{
    this->text = text;
    this->size = size;
    this->color = color;
    this->letter_spacing = letter_spacing;

    font = TTF_OpenFont("./assets/font/arial.ttf", size);

    if (!font)
    {
        cerr << "Erreur chargement font : "
                  << TTF_GetError() << endl;
    }
}

void Text::render(int origin_x, int origin_y)
{
    renderText(app->renderer, font, text, origin_x + x, origin_y + y,
        color, letter_spacing);
}

int Text::measureWidth() const
{
    return measureTextWidth(font, text, letter_spacing);
}

Text::~Text()
{
    if (font)
        TTF_CloseFont(font);
}