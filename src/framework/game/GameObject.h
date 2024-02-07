#pragma once

#include "std.h"
#include <tsl/ordered_map.h>

class BaseGame;
class GameComponent;

class GameObject {
public:
    friend class BaseGame;

    explicit GameObject(BaseGame* game);
    virtual ~GameObject() = default;
    virtual void Update(double deltaTime) = 0;
    virtual void Render() = 0;

    template<class Component>
    void AddComponent(std::shared_ptr<Component> component);

    template<class Component>
    std::shared_ptr<Component> GetComponent();

    template<class Component>
    void RemoveComponent();

    template<class GameObjectType>
    void AddChild(std::shared_ptr<GameObjectType> child) {
        child->parent = this;
        children.push_back(std::dynamic_pointer_cast<GameObject*>(child));
    }

    template<class GameObjectType>
    void RemoveChild(std::shared_ptr<GameObjectType> child) {
        children.remove(std::dynamic_pointer_cast<GameObject*>(child));
    }

protected:
    GameObject* parent = nullptr;
    BaseGame* game = nullptr;
    tsl::ordered_map<std::string, std::shared_ptr<GameComponent>> components;
    std::list<std::shared_ptr<GameObject>> children;
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
