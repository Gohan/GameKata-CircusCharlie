#pragma once
#include "framework/game/GameObject.h"

class Game;
namespace kata2024::game::objects {
    class Player : public GameObject {
    public:
        explicit Player(Game* game);
        ~Player() override;
        void Update(double deltaTime) override;
        void Render() override;
    };
}



