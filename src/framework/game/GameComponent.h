#pragma once

#include "std.h"

class GameObject;

class GameComponent {
public:
    explicit GameComponent(GameObject* gameObject);
    virtual ~GameComponent() = 0;
    virtual void Update(double deltaTime);
    virtual void Render();

private:
    GameObject* gameObject;
};