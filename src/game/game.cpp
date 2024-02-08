#include "std.h"
#include "SDL.h"
#include "game.h"
#include "framework/services/ControllerGameService.h"
#include "game/objects/Player.h"

using namespace kata2024::game::objects;

Game::Game() {
}

Game::~Game() {
}

void Game::OnInitialize() {
    BaseGame::OnInitialize();

    AddGameObject(std::make_shared<Player>(this));
}
