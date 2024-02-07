//
// Created by cppgo on 2024/2/6.
//
#pragma once

#include "std.h"
#include <SDL.h>
template<class Game>
class GameServiceContainer;

class BaseGame {
public:
    BaseGame();
    virtual ~BaseGame();
    void Init(const std::string& title, int windowWidth, int windowHeight);
    void RunLoop();
    SDL_Window* Window();

protected:
    virtual void Update(double deltaTime);
    virtual void Render();

private:
    bool isExit = false;
    uint64_t lastTime = 0;
    uint64_t nowTime = 0;
    uint64_t nextTick = 0;
    std::tm time = {};
    std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> window;
    std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>> renderer;
    std::unique_ptr<GameServiceContainer<BaseGame>> container;
};