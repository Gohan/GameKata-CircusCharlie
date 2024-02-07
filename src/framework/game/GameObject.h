#pragma once

#include "std.h"
#include <tsl/ordered_map.h>

class BaseGame;
class GameComponent;

class GameObject {
public:
    explicit GameObject(BaseGame* game) { this->game = game; }

    template<class Component>
    void AddComponent(std::shared_ptr<Component> component);

    template<class Component>
    std::shared_ptr<Component> GetComponent();

    template<class Component>
    void RemoveComponent();

    virtual ~GameObject() = default;
protected:
    BaseGame* game;
    tsl::ordered_map<std::string, std::shared_ptr<GameComponent>> components;
};

template<class Component>
void GameObject::AddComponent(std::shared_ptr<Component> component) {
    components[typeid(Component).name()] = component;
}

template<class Component>
std::shared_ptr<Component> GameObject::GetComponent() {
    return std::dynamic_pointer_cast<Component>(components[typeid(Component).name()]);
}

template<class Component>
void GameObject::RemoveComponent() {
    components.erase(typeid(Component).name());
}
