#pragma once

#include "GameServiceContainer.h"

class ControllerGameService : public IService {
public:
    explicit ControllerGameService(BaseGame* game) {
        this->game = game;
    }

    ~ControllerGameService() override = default;
private:
    BaseGame* game;
};
