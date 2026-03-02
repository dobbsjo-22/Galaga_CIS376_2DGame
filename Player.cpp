#include "Player.hpp"
#include <SDL3_image/SDL_image.h>

std::unordered_map<std::string, SDL_Texture*> Player::textureCache;

SDL_Texture* Player::getTexture(SDL_Renderer* renderer, const std::string& path) {
    auto it = textureCache.find(path);
    if (it != textureCache.end()) return it->second;

    const char* base = SDL_GetBasePath(); // folder containing the executable
    std::string fullPath = std::string(base) + "player.png";
    SDL_Surface* surface = IMG_Load(fullPath.c_str());
    if (!surface) {
        SDL_Log("Player IMG_Load failed for %s: %s", path.c_str(), SDL_GetError());
        return nullptr;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    if (!tex) {
        SDL_Log("Player CreateTextureFromSurface failed: %s", SDL_GetError());
        return nullptr;
    }

    // Useful for PNG transparency
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);

    textureCache[path] = tex;
    return tex;
}

Player::Player() : state(PlayerState::ALIVE), velocityX(0.0f), speed(5.0f), deathStartTime(0) {
    rect = { 375.0f, 540.0f, 64.0f, 64.0f };
}

bool Player::init(SDL_Renderer* renderer, const char* spritePathIn) {
    spritePath = spritePathIn ? spritePathIn : "player.png";

    int w = 0, h = 0;
    SDL_GetRenderOutputSize(renderer, &w, &h);
    screenW = (float)w;
    screenH = (float)h;

    rect.w = 64.0f;
    rect.h = 64.0f;

    // Bottom-middle spawn (fullscreen-safe)
    rect.x = (screenW - rect.w) * 0.5f;
    rect.y = screenH - rect.h;

    texture = getTexture(renderer, spritePath);
    return texture != nullptr;
}

void Player::handleInput(const SDL_Event&) {
    // Held-key movement (smooth, simple)
    const bool* keys = SDL_GetKeyboardState(nullptr);

    if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]) {
        velocityX = -speed;
    } else if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]) {
        velocityX = speed;
    } else {
        velocityX = 0.0f;
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
        if (texture) {
            SDL_RenderTexture(renderer, texture, nullptr, &rect);
        } else {
            // fallback: visible white rect if sprite failed to load
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
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