#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL3/SDL.h>

class Player {
public:
    Player();
    void handleInput(const SDL_Event& event);
    void update();
    void render(SDL_Renderer* renderer);
    bool wantsToShoot(const SDL_Event& event);

    SDL_FRect getRect() const { return rect; }

private:
    SDL_FRect rect;
    float speed;
    float velocityX; // How fast we are moving right now
};

#endif