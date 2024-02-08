#pragma once

#include "GameServiceContainer.h"

class BaseGame;
class TextureService : public IService<BaseGame> {
public:
    explicit TextureService(BaseGame* game) {
        this->game = game;
    };

    ~TextureService() override {};

    SDL_Texture* LoadTexture(const std::string& path);
    void UnloadTexture(const std::string& path);

private:
    std::unordered_map<std::string, SDL_Texture*> textures;
};
