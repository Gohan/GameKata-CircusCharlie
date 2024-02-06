//
// Created by cppgo on 2024/2/6.
//
module;

#ifndef FAKE_MODULE_INCLUDE
#include "config.h"
#endif

module Config;
import Game;

Game* Config::Game() {
    return static_cast<class Game*>(s_pGame);
}