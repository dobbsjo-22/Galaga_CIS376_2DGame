#include "Projectile.hpp"
#include <SDL3_image/SDL_image.h>

std::unordered_map<std::string, SDL_Texture*> Projectile::textureCache;

SDL_Texture* Projectile::getTexture(SDL_Renderer* renderer,const std::string& path) {
    auto it = textureCache.find(path);
    if (it != textureCache.end())
        return it->second;

    const char* base = SDL_GetBasePath(); // folder containing the executable
    std::string fullPath = std::string(base) + "bullet.png";
    SDL_Surface* surface = IMG_Load(fullPath.c_str());
    if (!surface) {
        SDL_Log("Bullet IMG_Load failed for %s: %s", path.c_str(), SDL_GetError());
        return nullptr;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    if (!tex) {
        SDL_Log("Bullet texture creation failed: %s", SDL_GetError());
        return nullptr;
    }

    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);

    textureCache[path] = tex;
    return tex;
}

Projectile::Projectile(float x, float y, ProjectileType type) : type(type), active(true) {
    rect = { x - 5.0f, y, 20.0f, 20.0f };
    
    if (type == ProjectileType::PLAYER) {
        speed = -7.0f; // Up
    } else {
        speed = 7.0f;  // Down
    }
    active = true;
}

void Projectile::update() {
    rect.y += speed;

    if (rect.y + rect.h < 0) {
        active = false;
    }
    if (rect.y > 2000.0f) { // quick safety
        active = false;
    }
}

void Projectile::render(SDL_Renderer* renderer) {
    if (type == ProjectileType::PLAYER) {
        if (!texture) {
            texture = getTexture(renderer, spritePath);
        }

        if (texture) {
            SDL_RenderTexture(renderer, texture, nullptr, &rect);
        } else {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(renderer, &rect);
        }
    } else {
        SDL_SetRenderDrawColor(renderer, 139, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
}