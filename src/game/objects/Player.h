#pragma once

#include "std.h"
#include "framework/game/GameObject.h"
#include "framework/services/RenderService.h"

class RenderService;
class SDL_Texture;

class Game;
namespace kata2024::game::objects {
    class Player : public GameObject {
    public:
        explicit Player(Game* game);
        ~Player() override;
        void Update(double deltaTime) override;
        void Render() override;
    private:
        std::shared_ptr<RenderService> textureService;
        std::unique_ptr<RenderService::SpriteAnimation> animatePlayRunning;
        std::unique_ptr<RenderService::SpriteAnimation> animateFired;
        SDL_Texture* texture;
        double deltaTime = 0;
    };

}



