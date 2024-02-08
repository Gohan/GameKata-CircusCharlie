//
// Created by cppgo on 2024/2/7.
//

#include "Player.h"
#include "game/game.h"
#include "framework/services/TextureService.h"

using namespace kata2024::game::objects;

Player::~Player() {
}

Player::Player(Game* game) : GameObject(game) {
    textureService = game->GetService<TextureService>();
    texture = textureService->LoadTexture("assets/Man.png");
}

void Player::Update(double deltaTime) {
    SDL_LogVerbose(SDL_LOG_CATEGORY_APPLICATION, "Player::Update: %f", deltaTime);
}

void Player::Render() {
    SDL_RenderCopyEx(game->Renderer(), texture, nullptr, nullptr, 0, nullptr, SDL_FLIP_NONE);
}
