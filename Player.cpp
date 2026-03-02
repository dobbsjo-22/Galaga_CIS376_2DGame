#include "Player.hpp"

Player::Player() : state(PlayerState::ALIVE), velocityX(0.0f), speed(5.0f), deathStartTime(0) {
    rect = { 375.0f, 540.0f, 50.0f, 50.0f };
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
    if (state == PlayerState::ALIVE) {
        rect.x += velocityX;
        if (rect.x < 0) rect.x = 0;
        if (rect.x > 800 - rect.w) rect.x = 800 - rect.w;
    } 
    else if (state == PlayerState::DYING) {
        // Check if 1.5 seconds have passed
        if (SDL_GetTicks() - deathStartTime > deathDuration) {
            state = PlayerState::DEAD;
        }
    }
}

void Player::render(SDL_Renderer* renderer) {
    if (state == PlayerState::DEAD) return;

    if (state == PlayerState::DYING) {
        // Blink logic: Change color every 250ms
        // (CurrentTime / 250) % 2 will alternate between 0 and 1
        if ((SDL_GetTicks() / 250) % 2 == 0) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red blink
            SDL_RenderFillRect(renderer, &rect);
        }
        // If 1, we draw nothing (invisible blink)
    } else {
        // Normal Alive State
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
        SDL_RenderFillRect(renderer, &rect);
    }
}

void Player::killPlayer() {
    if (state == PlayerState::ALIVE) {
        state = PlayerState::DYING;
        deathStartTime = SDL_GetTicks();
    }
}

bool Player::wantsToShoot(const SDL_Event& event) {
    if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_SPACE) {
        return true;
    }
    return false;
}