#pragma once

#include "GameServiceContainer.h"
#include <absl/strings/string_view.h>

class BaseGame;

class RenderService : public IService<BaseGame> {
public:
    struct SpriteSheets {
        const char* name;
        int16_t frameWidth;
        int16_t frameHeight;
        int16_t frameRate;
        int16_t frameStart;
        int16_t frameEnd;
        SDL_Texture* texture;
    };

    explicit RenderService(BaseGame* game) {
        this->game = game;
    };

    ~RenderService() override;

    SDL_Texture* LoadTexture(const std::string& path);
    void UnloadTexture(const std::string& path);
    SpriteSheets* PreparedSpriteSheet(
            const std::string& name, SDL_Texture* texture,
            int8_t frameWidth, int8_t frameHeight,
            int8_t frameRate, int8_t frameStart, int8_t frameEnd
    );

private:
    std::unordered_map<std::string, SDL_Texture*> textures;
    std::unordered_map<std::string, std::unique_ptr<SpriteSheets>> spriteSheets;
};
