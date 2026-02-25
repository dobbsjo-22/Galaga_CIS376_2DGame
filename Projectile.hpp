#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SDL3/SDL.h>

class Projectile {
public:
    Projectile(float x, float y);
    void update();
    void render(SDL_Renderer* renderer);

    SDL_FRect rect;
    bool active;
    float speed;
};

#endif