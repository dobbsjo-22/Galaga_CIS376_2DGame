#include <SDL3/SDL.h>
#include <vector>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Projectile.hpp"
#include "Score.hpp"
#include <algorithm>

// Helper function for collision
bool checkCollision(SDL_FRect a, SDL_FRect b) {
    return (a.x < b.x + b.w &&
            a.x + a.w > b.x &&
            a.y < b.y + b.h &&
            a.y + a.h > b.y);
}

class GalagaGame {
public:
    GalagaGame() : window(nullptr), renderer(nullptr), isRunning(false), enemySpeed(2.0f) {}

    bool init(const char* title, int width, int height) {
        if (!SDL_Init(SDL_INIT_VIDEO)) return false;
        window = SDL_CreateWindow(title, width, height, SDL_WINDOW_FULLSCREEN);
        renderer = SDL_CreateRenderer(window, NULL);
        player.init(renderer, "player.png");

        // this makes the enemies
        for (int i = 0; i < 5; ++i) {
            enemies.emplace_back(150.0f + (i * 100.0f), 50.0f, "enemy.png");
        }

        isRunning = true;
        return true;
    }

    // this handles the player inputs and the programming shutting down
    void handleEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) isRunning = false;
        }

        // held-key movement
        player.handleInput(event); // event param unused; ok for now

        // held-key shooting with cooldown
        if (player.wantsToShoot()) {
            bullets.push_back(Projectile(player.getRect().x, player.getRect().y, ProjectileType::PLAYER));
        }
    }


    void update() {
        // 1. Update Player (only if alive)
        if (player.getState() == PlayerState::ALIVE) {
            player.update();
        }

        // 2. Enemy Shooting Logic
        for (auto& e : enemies) {
            if (e.tryToShoot()) {
                bullets.push_back(Projectile(e.rect.x, e.rect.y, ProjectileType::ENEMY));
            }
        }

        // 3. Update all Bullets
        for (auto& b : bullets) {
            b.update();
        }

        // 4. Collision Handling
        for (auto& b : bullets) {
            if (!b.active) continue; // Skip bullets already spent this frame

            // PLAYER BULLETS vs ENEMIES
            if (b.getType() == ProjectileType::PLAYER) {
                for (auto it = enemies.begin(); it != enemies.end(); ) {
                    if (checkCollision(b.rect, it->rect)) {
                        b.active = false;          // Mark bullet for deletion
                        it = enemies.erase(it);    // Remove enemy and update iterator
                        score.addPoints(10);       // Add points
                        break;                     // Stop checking THIS bullet; it's gone
                    } else {
                        ++it;
                    }
                }
            }
            // ENEMY BULLETS vs PLAYER
            else if (b.getType() == ProjectileType::ENEMY && player.getState() == PlayerState::ALIVE) {
                if (checkCollision(b.rect, player.getRect())) {
                    b.active = false;
                    player.killPlayer();
                }
            }
        }

        // 5. PLAYER vs ENEMY SHIP (Body Crash)
        if (player.getState() == PlayerState::ALIVE) {
            for (auto& e : enemies) {
                if (checkCollision(player.getRect(), e.rect)) {
                    player.killPlayer();
                    // Optional: You could also destroy the enemy ship here
                    break; 
                }
            }
        }

        // 6. Cleanup inactive bullets
        bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
            [](const Projectile& b) { return !b.active; }), bullets.end());

        int screenW = 0, screenH = 0;
        SDL_GetRenderOutputSize(renderer, &screenW, &screenH);

        // 7. Enemy Swarm Movement Logic
        bool hitWall = false;
        if (!enemies.empty()) {
            float leftMost = enemies.front().rect.x;
            float rightMost = enemies.front().rect.x + enemies.front().rect.w;

            for (auto& e : enemies) {
                leftMost = std::min(leftMost, e.rect.x);
                rightMost = std::max(rightMost, e.rect.x + e.rect.w);
            }

            // Bounce if the formation hits either side of the screen
            if (leftMost <= 0.0f || rightMost >= (float)screenW) {
                hitWall = true;
            }
        }

        if (hitWall) {
            enemySpeed *= -1; // Reverse direction
            // Nudge all enemies once so they don't trigger "hitWall" again immediately
            for (auto& e : enemies) {
                e.rect.x += enemySpeed;
            }
        }

        // Apply movement to all enemies
        for (auto& e : enemies) {
            e.update(enemySpeed);
        }
    }

    void updateWindowTitle() {
        std::string title = "Galaga - " + score.getScoreString();
        SDL_SetWindowTitle(window, title.c_str());
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
    Score score;
    
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

