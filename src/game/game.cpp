#include "game.h"
#include "sdl.h"

Game::Game() {
}

void Game::Init(const std::string& title, int windowWidth, int windowHeight) {
    window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>>(
            SDL_CreateWindow(
                    title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                    windowWidth, windowHeight, 0
            ), SDL_DestroyWindow
    );
}

SDL_Window* Game::Window() {
    return window.get();
}


