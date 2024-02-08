//
// Created by cppgo on 2024/2/8.
//

#include "RenderService.h"
#include <SDL.h>
#include <SDL_image.h>

#include <memory>
#include "framework/game/BaseGame.h"

SDL_Texture* RenderService::LoadTexture(const absl::string_view& path) {
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

void RenderService::UnloadTexture(const absl::string_view& path) {
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
        const absl::string_view& name,
        SDL_Texture* texture,
        int16_t frameWidth,
        int16_t frameHeight,
        int16_t frameRate,
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

RenderService::SpriteAnimation* RenderService::CreateSpriteAnimation(RenderService::SpriteSheets* spriteSheet) {
    if (spriteSheet == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SpriteSheet is null");
        return nullptr;
    }
    return new SpriteAnimation{
            .spriteSheet = spriteSheet,
            .frame = 0,
            .totalTicks = 0,
    };
}

RenderService::SpriteAnimation* RenderService::CreateSpriteAnimation(const absl::string_view& name) {
    auto lookup = spriteSheets.find(name);
    if (lookup == spriteSheets.end()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SpriteSheet not found: %s", name.data());
        return nullptr;
    }
    return new SpriteAnimation{
            .spriteSheet = (*lookup).second.get(),
            .frame = 0,
            .totalTicks = 0,
    };
}

void RenderService::UpdateAnimation(RenderService::SpriteAnimation* animation, double deltaTime) {
    if (animation == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SpriteAnimation is null");
        return;
    }
    auto spriteSheet = animation->spriteSheet;
    animation->totalTicks += deltaTime;
    if (animation->totalTicks > spriteSheet->frameRate) {
        animation->frame++;
        if (animation->frame >= spriteSheet->frameEnd) {
            animation->frame = spriteSheet->frameStart;
        }
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Add SpriteAnimation: %s, frame: %d, %d, %lf, %llu", spriteSheet->name,
                    animation->frame, animation->totalTicks, deltaTime, SDL_GetPerformanceFrequency());
        animation->totalTicks -= spriteSheet->frameRate;
    } else {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "SpriteAnimation: %s, frame: %d, %d", spriteSheet->name,
                    animation->frame, animation->totalTicks);
    }
}

void RenderService::RenderAnimation(RenderService::SpriteAnimation* animation) {
    if (animation == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SpriteAnimation is null");
        return;
    }
    auto spriteSheet = animation->spriteSheet;
    SDL_Rect srcRect {
            .x = spriteSheet->frameWidth * animation->frame,
            .y = 0,
            .w = spriteSheet->frameWidth,
            .h = spriteSheet->frameHeight,
    };
    SDL_Rect dstRect {
            .x = 0,
            .y = 0,
            .w = spriteSheet->frameWidth,
            .h = spriteSheet->frameHeight,
    };
    SDL_RenderCopyEx(game->Renderer(), spriteSheet->texture, &srcRect, &dstRect, 0, nullptr, SDL_FLIP_NONE);
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "RenderAnimation: %s, frame: %d, %d", spriteSheet->name,
                animation->frame, animation->totalTicks);
}