#include "GameComponent.h"
#include "GameObject.h"

GameComponent::~GameComponent() = default;

GameComponent::GameComponent(GameObject* gameObject) {
    this->gameObject = gameObject;
}

void GameComponent::Update(double deltaTime) {
}

void GameComponent::Render() {
}
