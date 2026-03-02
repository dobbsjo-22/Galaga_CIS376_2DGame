#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL3/SDL.h>

enum class PlayerState { ALIVE, DYING, DEAD };

class Player {
public:
    Player();
    void handleInput(const SDL_Event& event);
    void update();
    void render(SDL_Renderer* renderer);
    bool wantsToShoot(const SDL_Event& event);
    void killPlayer();

    PlayerState getState() const { return state; }

    SDL_FRect getRect() const { return rect; }

private:
    SDL_FRect rect;
    float speed;
    float velocityX; // How fast we are moving right now

    PlayerState state;
    Uint64 deathStartTime;
    const Uint64 deathDuration = 1500; // 1.5 seconds total
};

#endif