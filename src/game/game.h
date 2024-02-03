#ifndef GAMEKATA_GAME_H
#define GAMEKATA_GAME_H

#include "sdl.h"
#include <memory>
#include <functional>

class Game {
public:
    Game();
    void Init(const std::string& title, int windowWidth, int windowHeight);
    SDL_Window* Window();

private:
    std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> window;
};

#endif //GAMEKATA_GAME_H
