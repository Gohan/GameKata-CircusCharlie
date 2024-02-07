#pragma once

class GameComponent {
    virtual ~GameComponent() = 0;
};
GameComponent::~GameComponent() = default;