//
// Created by cppgo on 2024/2/6.
//
#pragma once

#include "std.h"
#include <tsl/ordered_set.h>
#include <SDL.h>

template<class Game>
class GameServiceContainer;

class GameObject;

class GameObjectOperation {
public:
    enum class Operation {
        Add,
        Remove,
    };
public:
    GameObjectOperation(
            Operation operation,
            std::shared_ptr<GameObject> gameObject
    ) : operation(operation), gameObject(gameObject) {}
    Operation operation;
    std::shared_ptr<GameObject> gameObject;
};

class BaseGame {
    friend class BaseGameTest;
    enum class GameState {
        BeforeUpdate,
        Updating,
        AfterUpdate,
    };
public:
    BaseGame();
    virtual ~BaseGame();
    void Init(const std::string& title, int windowWidth, int windowHeight);
    void CleanUp();
    void RunLoop();
    SDL_Window* Window();
    void AddGameObject(std::shared_ptr<GameObject> gameObject);
    void RemoveGameObject(std::shared_ptr<GameObject> gameObject);

protected:
    uint64_t TickUpdate(SDL_Event& e);
    bool RunLoopOnce(SDL_Event& e);
    virtual void Update(double deltaTime);
    virtual void Render();
    void ProcessGameObjectOperations();
    std::unique_ptr<GameServiceContainer<BaseGame>> container;
    tsl::ordered_set<std::shared_ptr<GameObject>> gameObjects;
    std::list<GameObjectOperation> gameObjectOperations;

private:
    bool isExit = false;
    uint64_t lastTime = 0;
    uint64_t nowTime = 0;
    uint64_t nextTick = 0;
    std::tm time = {};
    std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> window;
    std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>> renderer;
    GameState gameState = GameState::BeforeUpdate;
};