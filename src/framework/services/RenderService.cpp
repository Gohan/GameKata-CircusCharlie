//
// Created by cppgo on 2024/2/8.
//

#include "RenderService.h"
#include <SDL.h>
#include <SDL_image.h>

#include <memory>
#include "framework/game/BaseGame.h"

SDL_Texture* RenderService::LoadTexture(const std::string& path) {
    auto surface = IMG_Load(path.data());
    if (surface == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load texture: %s", path.data());
        return nullptr;
    }

    auto texture = textures[path];
    if (texture != nullptr) {
        return texture;
    }

    texture = SDL_CreateTextureFromSurface(game->Renderer(), surface);
    SDL_FreeSurface(surface);
    textures[path] = texture;
    return texture;
}

void RenderService::UnloadTexture(const std::string& path) {
    auto texture = textures[path];
    if (texture == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Texture not found: %s", path.data());
        return;
    }

    SDL_DestroyTexture(texture);
    textures.erase(path);
}

RenderService::~RenderService() {
    for (auto& [path, texture]: textures) {
        SDL_DestroyTexture(texture);
    }
    textures.clear();
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "RenderService destroyed");
}

RenderService::SpriteSheets* RenderService::PreparedSpriteSheet(
        const std::string& name,
        SDL_Texture* texture,
        int8_t frameWidth,
        int8_t frameHeight,
        int8_t frameRate,
        int8_t frameStart,
        int8_t frameEnd
) {
    auto lookup = spriteSheets.find(name);
    if (lookup != spriteSheets.end()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SpriteSheet already exists: %s", name.data());
        return (*lookup).second.get();
    }
    auto spriteSheet = std::make_unique<SpriteSheets>(SpriteSheets{
            .name = name.data(),
            .frameWidth = frameWidth,
            .frameHeight = frameHeight,
            .frameRate = frameRate,
            .frameStart = frameStart,
            .frameEnd = frameEnd,
            .texture = texture,
    });
    spriteSheets[name] = std::move(spriteSheet);
    return spriteSheets[name].get();
}
