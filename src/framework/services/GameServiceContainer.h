#pragma once

#include "std.h"

class IService {
public:
    virtual ~IService() = 0;
};

class BaseGame;

class GameServiceContainer {
public:
    explicit GameServiceContainer(BaseGame* game);
    virtual ~GameServiceContainer() = default;

    template<class T = IService>
    void AddService(std::shared_ptr<T> service) {
        services[typeid(T).name()] = service;
    }

    template<class T = IService>
    std::shared_ptr<T> GetService() {
        return std::dynamic_pointer_cast<T>(services[typeid(T).name()]);
    };

private:
    std::map<std::string, std::shared_ptr<IService>> services;
    BaseGame* game;
};

