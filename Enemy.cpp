#include "Enemy.hpp"
#include <cstdlib>

std::unordered_map<std::string, SDL_Texture*> Enemy::textureCache;

SDL_Texture* Enemy::getTexture(SDL_Renderer* renderer,const std::string& path) {
    auto it = textureCache.find(path);
    if (it != textureCache.end())
        return it->second;

    const char* base = SDL_GetBasePath(); // folder containing the executable
    std::string fullPath = std::string(base) + "enemy.png";
    SDL_Surface* surface = IMG_Load(fullPath.c_str());
    if (!surface) {
        SDL_Log("IMG_Load failed for %s: %s", path.c_str(), SDL_GetError());
        return nullptr;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    if (!tex) {
        SDL_Log("CreateTextureFromSurface failed: %s", SDL_GetError());
        return nullptr;
    }

    textureCache[path] = tex;
    return tex;
}

Enemy::Enemy(float x, float y, const char* spritePath)
    : spritePath(spritePath)
{
    lastShootTime = SDL_GetTicks();
    nextShootDelay = 1000 + (rand() % 4000);
    rect.x = x;
    rect.y = y;
    rect.w = 64.0f;
    rect.h = 64.0f;
}

Enemy::~Enemy() {
}

void Enemy::update(float speed) {
    rect.x += speed;
}

void Enemy::render(SDL_Renderer* renderer) {
    if (!texture) {
        texture = getTexture(renderer, spritePath);
    }

    if (texture) {
        SDL_RenderTexture(renderer, texture, nullptr, &rect);
    }
    else {
        // fallback debug rectangle
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
}

bool Enemy::tryToShoot() {
    Uint64 currentTime = SDL_GetTicks();
    if (currentTime > lastShootTime + nextShootDelay) {
        lastShootTime = currentTime;
        nextShootDelay = 1000 + (rand() % 4000); // Reset for next shot
        return true;
    }
    return false;
}

