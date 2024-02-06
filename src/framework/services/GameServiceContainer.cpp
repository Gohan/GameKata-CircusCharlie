//
// Created by cppgo on 2024/2/6.
//

#include "GameServiceContainer.h"

GameServiceContainer::GameServiceContainer(BaseGame* game) {
    this->game = game;
}

IService::~IService() = default;