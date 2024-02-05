#pragma clang diagnostic push
module;

#include "std.h"
#include "SDL.h"
#include <gsl/gsl>

export module Game;

export class Game {
public:
    Game();
    virtual ~Game();
    void Init(const std::string& title, int windowWidth, int windowHeight);
    SDL_Window* Window();

private:
    std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> window;
    std::unique_ptr<SDL_Surface, std::function<void(SDL_Surface*)>> screen;
};

Game::Game() {
}

void Game::Init(const std::string& title, int windowWidth, int windowHeight) {
    window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>>(
            SDL_CreateWindow(
                    title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                    windowWidth, windowHeight, SDL_WINDOW_RESIZABLE
            ), SDL_DestroyWindow
    );
    screen = std::unique_ptr<SDL_Surface, std::function<void(SDL_Surface*)>>(
            SDL_GetWindowSurface(window.get()),
            [&](SDL_Surface* surface) {
                printf("SDL_DestroyWindowSurface: %p\n", window.get());
                SDL_DestroyWindowSurface(window.get());
            }
    );
}

SDL_Window* Game::Window() {
    return window.get();
}

Game::~Game() {
    screen = nullptr;
    window = nullptr;
}

#pragma clang diagnostic pop