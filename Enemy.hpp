#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SDL3/SDL.h>

class Enemy {
    public:
        Enemy(float x, float y);
        void update(float velocityX);
        void render(SDL_Renderer* renderer);
        bool tryToShoot(); // Checks if it's time to fire
        
        SDL_FRect rect;

    private:
        Uint64 lastShootTime;
        Uint64 nextShootDelay;
};

#endif