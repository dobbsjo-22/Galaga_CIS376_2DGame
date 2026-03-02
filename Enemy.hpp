#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SDL3/SDL.h>
#include <string>
#include <unordered_map>
#include <SDL3_image/SDL_image.h>

class Enemy {
public:
    Enemy(float x, float y, const char* spritePath);
    ~Enemy();

    void update(float speed);
    void render(SDL_Renderer* renderer);

    SDL_FRect rect{};

private:
    SDL_Texture* texture = nullptr;
    std::string spritePath;

    // Shared texture cache (load once, reuse)
    static std::unordered_map<std::string, SDL_Texture*> textureCache;

    static SDL_Texture* getTexture(SDL_Renderer* renderer,const std::string& path);
};

#endif