#include <SDL3/SDL.h>
#include <vector>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Projectile.hpp"
#include <algorithm>

// Helper function for collision
bool checkCollision(SDL_FRect a, SDL_FRect b) {
    return (a.x < b.x + b.w && 
            a.x + a.w > b.x &&
            a.y < b.y + b.h && 
            a.y + a.w > b.y);
}

class GalagaGame {
public:
    GalagaGame() : window(nullptr), renderer(nullptr), isRunning(false), enemySpeed(2.0f) {}

    bool init(const char* title, int width, int height) {
        if (!SDL_Init(SDL_INIT_VIDEO)) return false;
        window = SDL_CreateWindow(title, width, height, 0);
        renderer = SDL_CreateRenderer(window, NULL);

        // this makes the enemies
        for (int i = 0; i < 5; ++i) {
            enemies.push_back(Enemy(150.0f + (i * 100.0f), 50.0f));
        }

        isRunning = true;
        return true;
    }

    // this handles the player inputs and the programming shutting down
    void handleEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) isRunning = false;
            player.handleInput(event);
            
            if (player.wantsToShoot(event)) {
                bullets.push_back(Projectile(player.getRect().x, player.getRect().y));
            }
        }
    }

    void update() {
        player.update();

        // update bullets
        for (auto& b : bullets) b.update();

        // check Collisions (Bullet vs Enemy)
        for (auto& b : bullets) {
            for (auto it = enemies.begin(); it != enemies.end(); ) {
                if (checkCollision(b.rect, it->rect)) {
                    b.active = false;          // Kill bullet
                    it = enemies.erase(it);    // Kill enemy
                } else {
                    ++it;
                }
            }
        }

        // this does a cleanup on inactive bullets
        bullets.erase(std::remove_if(bullets.begin(), bullets.end(), 
            [](const Projectile& b) { return !b.active; }), bullets.end());

        // this changes the direction of the enemy group forcing the whole group to start moving the opposite way
        bool hitWall = false;
        for (auto& e : enemies) {
            if (e.rect.x <= 0 || e.rect.x >= 800 - e.rect.w) {
                hitWall = true;
                break;
            }
        }
        if (hitWall) {
            enemySpeed *= -1;
            // Nudge them away from the wall so they dont get stuck
            for (auto& e : enemies) e.rect.x += enemySpeed;
        }

        for (auto& e : enemies) {
            e.update(enemySpeed);
        }
    }

    void render() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        player.render(renderer);
        for (auto& b : bullets) b.render(renderer);
        for (auto& e : enemies) e.render(renderer);
        
        SDL_RenderPresent(renderer);
    }

    void clean() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    bool running() { return isRunning; }

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;
    Player player;
    
    std::vector<Enemy> enemies;
    float enemySpeed;
    std::vector<Projectile> bullets;
};

int main(int argc, char* argv[]) {
    GalagaGame game;
    if (game.init("Galaga - The Swarm", 800, 600)) {
        while (game.running()) {
            game.handleEvents();
            game.update();
            game.render();
            SDL_Delay(16);
        }
    }
    game.clean();
    return 0;
}

