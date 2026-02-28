#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL3/SDL.h>
#include <string>
#include <unordered_map>

class Player {
public:
    Player();

    // Call once after renderer is created (in your game's init)
    bool init(SDL_Renderer* renderer, const char* spritePath);

    void handleInput(const SDL_Event& event);
    void update();
    void render(SDL_Renderer* renderer);

    bool wantsToShoot();

    // For bullet spawn (center-top)
    float gunX() const { return rect.x + rect.w * 0.5f; }
    float gunY() const { return rect.y; }

    SDL_FRect getRect() const { return rect; }

private:
    SDL_FRect rect{};
    float speed = 5.0f;
    float velocityX = 0.0f;

    Uint64 lastShotMs = 0;
    Uint64 shotCooldownMs = 250;

    // Screen bounds (fullscreen-safe)
    float screenW = 800.0f;
    float screenH = 600.0f;

    // Sprite
    SDL_Texture* texture = nullptr;
    std::string spritePath;

    // Shared cache (load once)
    static std::unordered_map<std::string, SDL_Texture*> textureCache;
    static SDL_Texture* getTexture(SDL_Renderer* renderer, const std::string& path);
};

#endif