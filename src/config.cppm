module;

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

void Config::SetGame(void* pGame) {
    s_pGame = pGame;
}
