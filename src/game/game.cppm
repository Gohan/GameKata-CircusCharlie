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
    std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>> renderer;
};

Game::Game() {
}

void Game::Init(const std::string& title, int windowWidth, int windowHeight) {
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        exit(-1);
    }

    if (SDL_NumJoysticks() < 1) {
        printf("Warning: No joysticks connected!\n");
    } else {
        printf("Info: %d joysticks connected!\n", SDL_NumJoysticks());
    }

    window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>>(
            SDL_CreateWindow(
                    title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                    windowWidth, windowHeight, SDL_WINDOW_RESIZABLE
            ), SDL_DestroyWindow
    );
    renderer = std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>>(
            SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
            SDL_DestroyRenderer
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
    // printf_s("%llu: Render()\n", now);
    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 255, 255);
    SDL_RenderClear(renderer.get());
//    SDL_Rect rect {0, 0, 100, 100};
//    SDL_RenderFillRect(renderer.get(), &rect);
    SDL_RenderPresent(renderer.get());
}

SDL_Window* Game::Window() {
    return window.get();
}

Game::~Game() {
    renderer = nullptr;
    window = nullptr;
}