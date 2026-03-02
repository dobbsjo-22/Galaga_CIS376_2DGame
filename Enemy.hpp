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
        void update(float velocityX);
        void render(SDL_Renderer* renderer);
        bool tryToShoot();
        
        SDL_FRect rect{};

    private:
        Uint64 lastShootTime;
        Uint64 nextShootDelay;
        SDL_Texture* texture = nullptr;
        std::string spritePath;

        // Shared texture cache that we can load once and reuse
        static std::unordered_map<std::string, SDL_Texture*> textureCache;

        static SDL_Texture* getTexture(SDL_Renderer* renderer,const std::string& path);
};

#endif