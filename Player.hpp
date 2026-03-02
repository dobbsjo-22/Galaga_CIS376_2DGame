#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL3/SDL.h>
#include <string>
#include <unordered_map>

enum class PlayerState { ALIVE, DYING, DEAD };

class Player {
public:
    Player();

    bool init(SDL_Renderer* renderer, const char* spritePath);

    void handleInput(const SDL_Event& event);
    void update();
    void render(SDL_Renderer* renderer);

    bool wantsToShoot();
    void killPlayer();

    PlayerState getState() const { return state; }
  
    // For bullet spawn (center-top)
    float gunX() const { return rect.x + rect.w * 0.5f; }
    float gunY() const { return rect.y; }

    SDL_FRect getRect() const { return rect; }

private:
    SDL_FRect rect{};
    float speed = 5.0f;
    float velocityX = 0.0f;

    PlayerState state;
    Uint64 deathStartTime;
    const Uint64 deathDuration = 1500; // 1.5 seconds total
  
    Uint64 lastShotMs = 0;
    Uint64 shotCooldownMs = 250;

    float screenW = 800.0f;
    float screenH = 600.0f;

    SDL_Texture* texture = nullptr;
    std::string spritePath;

    static std::unordered_map<std::string, SDL_Texture*> textureCache;
    static SDL_Texture* getTexture(SDL_Renderer* renderer, const std::string& path);
};

#endif