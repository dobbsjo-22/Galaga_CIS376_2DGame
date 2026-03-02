#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SDL3/SDL.h>

enum class ProjectileType { PLAYER, ENEMY };

class Projectile {
public:
    Projectile(float x, float y, ProjectileType type);
    void update();
    void render(SDL_Renderer* renderer);

    SDL_FRect rect;
    bool active;
    float speed;
    ProjectileType type;
};

#endif