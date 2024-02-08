//
// Created by cppgo on 2024/2/7.
//

#include "Player.h"
#include "game/game.h"

using namespace kata2024::game::objects;

Player::~Player() {
}

Player::Player(Game* game) : GameObject(game) {
}

void Player::Update(double deltaTime) {
}

void Player::Render() {
}
