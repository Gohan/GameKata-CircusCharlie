//
// Created by cppgo on 2024/2/6.
//

#include "BaseGame.h"
#include "GameObject.h"
#include "../services/ControllerGameService.h"
#include "../services/GameServiceContainer.h"

BaseGame::BaseGame() {
    container = std::make_unique<GameServiceContainer<BaseGame>>(this);
}

void BaseGame::Init(const std::string& title, int windowWidth, int windowHeight) {
#ifdef KATA_DEBUG
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
#endif
    //Initialize SDL
    SDL_SetHint(SDL_HINT_JOYSTICK_RAWINPUT, "0");
    SDL_SetHint(SDL_HINT_JOYSTICK_THREAD, "1");
    SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        exit(0);
    }

    if (SDL_NumJoysticks() < 1) {
        printf("Warning: No joysticks connected!\n");
    } else {
        printf("Info: %d joysticks connected!\n", SDL_NumJoysticks());
    }

    window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window*) >>(
            SDL_CreateWindow(
                    title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                    windowWidth, windowHeight, SDL_WINDOW_RESIZABLE
            ), SDL_DestroyWindow
    );
    renderer = std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*) >>(
            SDL_CreateRenderer(window.get(), 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
            SDL_DestroyRenderer
    );
    container->AddService(std::make_shared<ControllerGameService>(this));
    auto spControllerGameService = container->GetService<ControllerGameService>();
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "spControllerGameService: %p", spControllerGameService.get());

    OnInitialize();
}

void BaseGame::CleanUp() {
    container->RemoveService<ControllerGameService>();
}

void BaseGame::RunLoop() {
    SDL_Event e;
    while (RunLoopOnce(e));
}

bool BaseGame::RunLoopOnce(SDL_Event& e) {
    if (!isExit) {
        lastTime = SDL_GetPerformanceCounter();
        nextTick = lastTime + (SDL_GetPerformanceFrequency() / 60);
        do {
            lastTime = TickUpdate(e);
        } while (SDL_GetPerformanceCounter() <= nextTick);
        Render();
    }
    return !isExit;
}

uint64_t BaseGame::TickUpdate(SDL_Event& e) {
    gameState = GameState::BeforeUpdate;
    while (SDL_PollEvent(&e)) {
        container->DispatchEvent(e);
        switch (e.type) {
            case SDL_QUIT:
                isExit = true;
                continue;
            default:
                break;
        }
    }
    ProcessGameObjectOperations();
    nowTime = SDL_GetPerformanceCounter();
    auto deltaTime = (double(nowTime - lastTime) * 1000 / (double) SDL_GetPerformanceFrequency());
    gameState = GameState::Updating;
    Update(deltaTime);
    gameState = GameState::AfterUpdate;
    return nowTime;
}

void BaseGame::Update(double deltaTime) {
    for (auto& gameObject: gameObjects) {
        gameObject.get()->Update(deltaTime);
    }
}

void BaseGame::Render() {
    auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
    // printf_s("%llu: Render()\n", now);
    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 255, 255);
    SDL_RenderClear(renderer.get());
//    SDL_Rect rect {-1, 0, 100, 100};
//    SDL_RenderFillRect(renderer.get(), &rect);
    for (auto& gameObject: gameObjects) {
        gameObject.get()->Render();
    }
    SDL_RenderPresent(renderer.get());
}

SDL_Window* BaseGame::Window() {
    return window.get();
}

BaseGame::~BaseGame() {
    renderer = nullptr;
    window = nullptr;
}

void BaseGame::AddGameObject(std::shared_ptr<GameObject> gameObject) {
    if (gameState == GameState::Updating) {
        gameObjectOperations.emplace_back(GameObjectOperation{GameObjectOperation::Operation::Add, gameObject});
        return;
    }
    if (gameObjects.contains(gameObject)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "GameObject already exists in gameObjects");
    }
    gameObjects.insert(gameObject);
}

void BaseGame::RemoveGameObject(std::shared_ptr<GameObject> gameObject) {
    if (gameState == GameState::Updating) {
        gameObjectOperations.emplace_back(GameObjectOperation{GameObjectOperation::Operation::Add, gameObject});
        return;
    }
    if (!gameObjects.contains(gameObject)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "GameObject not found in gameObjects");
    }
    gameObjects.erase(gameObject);
}

void BaseGame::ProcessGameObjectOperations() {
    assert(gameState != GameState::Updating);
    auto it = gameObjectOperations.begin();
    while (it != gameObjectOperations.end()) {
        auto& operation = *it;
        switch (operation.operation) {
            case GameObjectOperation::Operation::Add:
                AddGameObject(operation.gameObject);
                break;
            case GameObjectOperation::Operation::Remove:
                RemoveGameObject(operation.gameObject);
                break;
        }
        it = gameObjectOperations.erase(it);
    }
}
