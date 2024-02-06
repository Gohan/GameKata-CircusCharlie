//
// Created by cppgo on 2024/2/4.
//
export module Config;
import Game;
import GameService;

export class Config {
public:
    static Game* Game();
    static void SetGame(void* pGame);
private:
    static void* s_pGame;
};

void* Config::s_pGame = nullptr;

Game* Config::Game() {
    return static_cast<class Game*>(s_pGame);
}

void Config::SetGame(void* pGame) {
    s_pGame = pGame;
}
