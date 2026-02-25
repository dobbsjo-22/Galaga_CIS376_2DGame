#include "Projectile.hpp"

Projectile::Projectile(float x, float y) {
    // center the bullet on the player (Player width is 50, bullet is 10)
    rect = { x + 20.0f, y, 10.0f, 20.0f }; 
    speed = -7.0f; // negative moves UP in SDL coordinates bc cords start at top left
    active = true;
}

void Projectile::update() {
    rect.y += speed;
    // deactivate if it flies off the top of the screen
    if (rect.y + rect.h < 0) {
        active = false;
    }
}

void Projectile::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}