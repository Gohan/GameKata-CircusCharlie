//
// Created by cppgo on 2024/2/6.
//
module;

#include "std.h"

export module GameService:GameServiceContainer;

import :IService;

export class GameServiceContainer {
public:
    GameServiceContainer() = default;
    virtual ~GameServiceContainer() = default;

    template<class T = IService>
    void AddService(std::shared_ptr<T> service) {
        services[typeid(T).name()] = service;
    }

    template<class T = IService>
    std::shared_ptr<T> GetService() {
        return std::dynamic_pointer_cast<T>(services[typeid(T).name()]);
    }

private:
    std::map<std::string, std::shared_ptr<IService>> services;
};
