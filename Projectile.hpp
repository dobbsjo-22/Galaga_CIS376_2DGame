#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SDL3/SDL.h>
#include <string>
#include <unordered_map>

enum class ProjectileType { PLAYER, ENEMY };

class Projectile {
public:
    Projectile(float x, float y, ProjectileType type);
    void update();
    void render(SDL_Renderer* renderer);

    SDL_FRect rect{};
    bool active;

    ProjectileType getType() const { return type; }

private:
    float speed;
    ProjectileType type;

    SDL_Texture* texture = nullptr;
    std::string spritePath = "bullet.png";

    static std::unordered_map<std::string, SDL_Texture*> textureCache;
    static SDL_Texture* getTexture(SDL_Renderer* renderer,const std::string& path);
};

#endif