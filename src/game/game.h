#ifndef GAMEKATA_GAME_H
#define GAMEKATA_GAME_H

#include "SDL.h"
#include <gsl/gsl>
#include <memory>
#include <functional>

class Game {
public:
    Game();
    virtual ~Game();
    void Init(const std::string& title, int windowWidth, int windowHeight);
    SDL_Window* Window();

private:
    std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> window;
    std::unique_ptr<SDL_Surface, std::function<void(SDL_Surface*)>> screen;
};

#endif //GAMEKATA_GAME_H
