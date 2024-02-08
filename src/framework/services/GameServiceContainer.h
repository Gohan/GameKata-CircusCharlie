#pragma once

#include "std.h"
#include "tsl/ordered_map.h"
#include <SDL.h>

template<class Game>
class IService {
public:
    virtual ~IService() = default;
    Game* game = nullptr;
};

class ISDLEventProcessor {
public:
    virtual bool OnProcessEvent(SDL_Event& e) = 0;
};

class BaseGame;

template<class Game>
class GameServiceContainer {
public:
    explicit GameServiceContainer(Game* game) {
        this->game = game;
    }

    virtual ~GameServiceContainer() = default;

    template<class T = IService<Game>>
    void AddService(std::shared_ptr<T> service) {
        if (services.contains(typeid(T).name())) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Service already exists: %s", typeid(T).name());
            return;
        } else {
            SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Service added: %s", typeid(T).name());
        }
        services[typeid(T).name()] = service;
        if (auto sdlEventProcessor = dynamic_cast<ISDLEventProcessor*>(service.get())) {
            sdlEventProcessors.push_back(sdlEventProcessor);
        }
    }

    template<class T = IService<Game>>
    void RemoveService() {
        auto erasedService = services[typeid(T).name()];
        auto erased = services.erase(typeid(T).name());
        if (erased == 0) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Service not found: %s", typeid(T).name());
            return;
        }
        if (auto sdlEventProcessor = dynamic_cast<ISDLEventProcessor*>(erasedService.get())) {
            auto removeCount = sdlEventProcessors.remove(sdlEventProcessor);
            if (removeCount == 0) {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Service not found in sdlEventProcessors: %s", typeid(T).name());
            } else {
                SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Service removed from sdlEventProcessors: %s", typeid(T).name());
            }
        }
    }

    template<class T = IService<Game>>
    std::shared_ptr<T> GetService() {
        return std::dynamic_pointer_cast<T>(services[typeid(T).name()]);
    };

    void DispatchEvent(SDL_Event& e) {
        for (auto& sdlEventProcessor: sdlEventProcessors) {
            if (sdlEventProcessor->OnProcessEvent(e)) {
                return;
            }
        }
    }

private:
    tsl::ordered_map<std::string, std::shared_ptr<IService<Game>>> services;
    std::list<ISDLEventProcessor*> sdlEventProcessors;
    Game* game;
};

