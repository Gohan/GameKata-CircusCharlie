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
        int8_t frameStart;
        int8_t frameEnd;
        SDL_Texture* texture;
    };

    struct SpriteAnimation {
        SpriteSheets* spriteSheet;
        int8_t frame;
        float totalTicks;
    };

    explicit RenderService(BaseGame* game) {
        this->game = game;
    };

    ~RenderService() override;

    SDL_Texture* LoadTexture(const absl::string_view& path);
    void UnloadTexture(const absl::string_view& path);
    SpriteSheets* PreparedSpriteSheet(
            const absl::string_view& name, SDL_Texture* texture,
            int16_t frameWidth, int16_t frameHeight,
            int16_t frameRate, int8_t frameStart, int8_t frameEnd
    );
    SpriteAnimation* CreateSpriteAnimation(SpriteSheets* spriteSheet);
    SpriteAnimation* CreateSpriteAnimation(const absl::string_view& name);
    void UpdateAnimation(SpriteAnimation* animation, double deltaTime);
    void RenderAnimation(SpriteAnimation* animation);
private:
    std::unordered_map<absl::string_view, SDL_Texture*> textures;
    std::unordered_map<absl::string_view, std::unique_ptr<SpriteSheets>> spriteSheets;
};
