#ifndef GAME_RECT_H
#define GAME_RECT_H

#include <SDL3/SDL.h>

#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_rect.h"

class GameRect {
   private:
    SDL_FRect _rect;
    SDL_Color _color;

   public:
    GameRect(const SDL_FRect& rect, const SDL_Color& color) : _rect(rect), _color(color) {}

    ~GameRect() = default;

    GameRect(const GameRect&) = delete;
    GameRect& operator=(const GameRect&) = delete;
    GameRect(GameRect&&) = delete;
    GameRect& operator=(GameRect&&) = delete;

    [[nodiscard]] const SDL_FRect& getRect() const { return _rect; };
    [[nodiscard]] const SDL_Color& getColor() const { return _color; };
};

#endif