#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SDL3/SDL.h>
#include <string>
#include <unordered_map>

class Projectile {
public:
    Projectile(float x, float y);

    void update();
    void render(SDL_Renderer* renderer);

    SDL_FRect rect{};
    bool active;

private:
    float speed;

    // Sprite
    SDL_Texture* texture = nullptr;
    std::string spritePath = "bullet.png";

    // Shared texture cache
    static std::unordered_map<std::string, SDL_Texture*> textureCache;
    static SDL_Texture* getTexture(SDL_Renderer* renderer,const std::string& path);
};

#endif