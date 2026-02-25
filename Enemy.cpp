#include "Enemy.hpp"

Enemy::Enemy(float x, float y) {
    rect = { x, y, 40.0f, 40.0f };
}

void Enemy::update(float velocityX) {
    rect.x += velocityX;
}

void Enemy::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red
    SDL_RenderFillRect(renderer, &rect);
}