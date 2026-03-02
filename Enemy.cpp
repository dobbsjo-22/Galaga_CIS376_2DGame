#include "Enemy.hpp"
#include <cstdlib>

Enemy::Enemy(float x, float y) {
    rect = { x, y, 40.0f, 40.0f };
    lastShootTime = SDL_GetTicks();
    nextShootDelay = 1000 + (rand() % 4000); // 1 to 5 seconds
}

void Enemy::update(float velocityX) {
    rect.x += velocityX;
}

void Enemy::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red
    SDL_RenderFillRect(renderer, &rect);
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