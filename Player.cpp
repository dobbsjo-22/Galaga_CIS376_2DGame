#include "Player.hpp"

Player::Player() {
    // starting position Bottom Middle
    rect = { 375.0f, 540.0f, 50.0f, 50.0f };
    speed = 5.0f;
    velocityX = 0.0f;
}

void Player::handleInput(const SDL_Event& event) {
    // handles left and right movements
    const bool* keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]) {
        velocityX = -speed;
    } else if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]) {
        velocityX = speed;
    } else {
        velocityX = 0.0f; // Stop moving if no key is pressed
    }
}

void Player::update() {
    rect.x += velocityX;

    // Keep player inside screen bounds (0 to 800)
    if (rect.x < 0) rect.x = 0;
    if (rect.x > 800 - rect.w) rect.x = 800 - rect.w;
}

void Player::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
    SDL_RenderFillRect(renderer, &rect);
}

bool Player::wantsToShoot(const SDL_Event& event) {
    if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_SPACE) {
        return true;
    }
    return false;
}