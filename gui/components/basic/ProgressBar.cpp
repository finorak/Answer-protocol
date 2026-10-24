#include "ProgressBar.hpp"
#include "../utils.hpp"

ProgressBar::ProgressBar(App *app, int x, int y,
            int width, int height, SDL_Color color, int progression, SDL_Color progression_color, int border_radius, SDL_Color border_color)
    : Component(app, x, y)
{
    this->color = color;
    this->border_color = border_color;
    this->width = width;
    this->height = height;
    this->border_radius = border_radius;
    this->progression = progression;
    this->progression_color = progression_color;
}

void ProgressBar::render(int origin_x, int origin_y)
{
    SDL_Rect rect = {
        origin_x + x,
        origin_y + y,
        width,
        height
    };

    // Remplissage arrondi
    drawFilledRoundedRect(
        app->renderer,
        rect,
        this->border_radius,
        color
    );
    
    SDL_Rect progression_rect = {
        origin_x + x,
        origin_y + y,
        (width * progression) / 100,
        height
    };

    // Remplissage arrondi
    drawFilledRoundedRect(
        app->renderer,
        progression_rect,
        this->border_radius,
        progression_color
    );

    // Bordure arrondie
    drawRoundedBorder(
        app->renderer,
        rect,
        this->border_radius,
        border_color
    );


}
