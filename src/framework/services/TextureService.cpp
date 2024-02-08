//
// Created by cppgo on 2024/2/8.
//

#include "TextureService.h"
#include <SDL.h>
#include <SDL_image.h>
#include "framework/game/BaseGame.h"

SDL_Texture* TextureService::LoadTexture(const std::string& path) {
    auto surface = IMG_Load(path.c_str());
    if (surface == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load texture: %s", path.c_str());
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

void TextureService::UnloadTexture(const std::string& path) {
    auto texture = textures[path];
    if (texture == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Texture not found: %s", path.c_str());
        return;
    }

    SDL_DestroyTexture(texture);
    textures.erase(path);
}

TextureService::~TextureService() {
    for (auto& [path, texture]: textures) {
        SDL_DestroyTexture(texture);
    }
    textures.clear();
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "TextureService destroyed");
}
