//
// Created by cppgo on 2024/2/7.
//

#include "Player.h"
#include "game/game.h"
#include "framework/services/RenderService.h"
#include "game/configs/Textures.h"

using namespace kata2024::game::configs;
using namespace kata2024::game::objects;

Player::~Player() {
}

Player::Player(Game* game) : GameObject(game) {
    textureService = game->GetService<RenderService>();
    texture = textureService->LoadTexture(Textures::PLAYER_TEXTURE);
    textureService->PreparedSpriteSheet(SpriteSheets::PLAYER_RUN, texture, 64, 96, 300, 0, 2);
    animatePlayRunning = std::unique_ptr<RenderService::SpriteAnimation>(
            textureService->CreateSpriteAnimation(SpriteSheets::PLAYER_RUN)
    );
}

void Player::Update(double deltaTime) {
    textureService->UpdateAnimation(animatePlayRunning.get(), deltaTime);
    this->deltaTime += deltaTime;
}

void Player::Render() {
//    SDL_RenderCopyEx(game->Renderer(), texture, nullptr, nullptr, 0, nullptr, SDL_FLIP_NONE);
    textureService->RenderAnimation(animatePlayRunning.get());
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Player::Render: %lf", this->deltaTime);
    this->deltaTime = 0;
}
