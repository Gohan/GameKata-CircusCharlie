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

void Game::RunLoop() {
    SDL_Event e;
    lastTime = SDL_GetPerformanceCounter();
    while (!isExit) {
        nextTick = lastTime + (SDL_GetPerformanceFrequency() / 60);
        do {
            while (SDL_PollEvent(&e)) {
                switch (e.type) {
                    case SDL_QUIT:
                        isExit = true;
                        continue;
                }
            }
            nowTime = SDL_GetPerformanceCounter();
            auto deltaTime = (double(nowTime - lastTime) * 1000 / (double) SDL_GetPerformanceFrequency());
            Update(deltaTime);
            lastTime = nowTime;
        } while (SDL_GetPerformanceCounter() <= nextTick);
        Render();
    }
}

void Game::Update(double deltaTime) {
    // TODO: do update
}

void Game::Render() {
    auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
    printf_s("%llu: Render()\n", now);
}

SDL_Window* Game::Window() {
    return window.get();
}

Game::~Game() {
    screen = nullptr;
    window = nullptr;
}

#pragma clang diagnostic pop