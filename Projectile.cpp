#include "Projectile.hpp"

Projectile::Projectile(float x, float y, ProjectileType type) : type(type), active(true) {
    rect = { x + 20.0f, y, 10.0f, 20.0f };
    
    if (type == ProjectileType::PLAYER) {
        speed = -7.0f; // Up
    } else {
        speed = 7.0f;  // Down
    }
}

void Projectile::update() {
    rect.y += speed;
    if (rect.y < -50 || rect.y > 650) active = false; // Off-screen bounds
}

void Projectile::render(SDL_Renderer* renderer) {
    if (type == ProjectileType::PLAYER) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green
    } else {
        SDL_SetRenderDrawColor(renderer, 139, 0, 0, 255); // Dark Red
    }
    SDL_RenderFillRect(renderer, &rect);
}