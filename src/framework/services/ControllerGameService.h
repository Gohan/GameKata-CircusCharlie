#pragma once

#include "GameServiceContainer.h"

class ControllerGameService : public IService {
public:
    explicit ControllerGameService(BaseGame* game) {
        this->game = game;
    }
    virtual ~ControllerGameService() = default;
private:
    BaseGame* game;
};
