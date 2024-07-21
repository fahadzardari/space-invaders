//
// Created by mrzardari on 3/1/24.
//

#include "SDLManager.h"


SDLManager::SDLManager() {
    lastProjectile = std::chrono::steady_clock::now();
};

void SDLManager::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "Initialization Error for SDL" << SDL_GetError() << std::endl;
    if (!IMG_Init(IMG_INIT_PNG))
        std::cout << "Initialization Error for SDL IMAGE" << SDL_GetError() << std::endl;
}

void SDLManager::createWindow() {
    this->window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                    SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

SDL_Texture *SDLManager::loadTexture(const char *filePath) {
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(this->renderer, filePath);
    if (texture == NULL) {
        std::cout << "Error Loading Texture Error: " << SDL_GetError() << std::endl;
    }

    return texture;
}

void SDLManager::renderTexture(SDL_Texture *tex) {
    SDL_Rect dest;
    dest.x = SCREEN_WIDTH - (SCREEN_WIDTH / 2);
    dest.y = SCREEN_HEIGHT - 50;
    dest.w = 50;
    dest.h = 50;

    SDL_RenderCopy(this->renderer, tex, nullptr, &dest);
}

void SDLManager::clear() {
    SDL_RenderClear(this->renderer);
}

void SDLManager::render() {
//    renderEnemy(&enemy);
    moveEnemies();
    fireEnemyProjectile();
    renderEnemies();
    if(playersLives > 0) renderShip(&playerShip);
    renderProjectiles();
}

void SDLManager::display() {
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderPresent(this->renderer);
}

void SDLManager::cleanup() {
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
}

SDL_Renderer *SDLManager::getRenderer() {
    return this->renderer;
}

void SDLManager::renderShip(Ship *ship) {
    SDL_Rect dest;
    dest.x = static_cast<int> (ship->pos.x);
    dest.y = static_cast<int> (ship->pos.y);
    dest.w = 40;
    dest.h = 40;
    SDL_RenderCopy(this->renderer, ship->getTexture(), NULL, &dest);
}

void SDLManager::renderEnemy(Enemy *e) {
    SDL_Rect dest;
    dest.x = static_cast<int> (e->position.x);
    dest.y = static_cast<int> (e->position.y);
    dest.w = 40;
    dest.h = 40;
    SDL_RenderCopy(this->renderer, e->getTexture(), NULL, &dest);
}

void SDLManager::renderEnemies() {
    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
        std::vector<Enemy> &row = *it;
        for (auto i = row.begin(); i != row.end(); ++i) {
            Enemy &e = *i;
            renderEnemy(&e);
        }
    }
}

void SDLManager::renderProjectiles() {
    for (auto it = projectiles.begin(); it != projectiles.end();) {
        Projectile &p = *it;
        SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(this->renderer, p.getRect());
        p.updatePosition();
        if (p.getRect()->y < enemies_y) {
            if (checkCollision(&p)) {
                p.~Projectile();
                it = projectiles.erase(it);
                continue;
            }
        }
        if (p.getRect()->y < 0) {
            p.~Projectile();
            it = projectiles.erase(it);
        } else {
            it++;
        }
    }
    for (auto it = enemyProjectiles.begin(); it != enemyProjectiles.end();) {
        Projectile &p = *it;
        SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(this->renderer, p.getRect());
        p.updatePosition();
        if (p.getRect()->y > 100) {
            if (checkCollisionEnemyProjectile(&p)) {
                p.~Projectile();
                it = enemyProjectiles.erase(it);
                continue;
            }
        }
        if (p.getRect()->y > SCREEN_HEIGHT) {
            p.~Projectile();
            it = enemyProjectiles.erase(it);
        } else {
            it++;
        }
    }
}

void SDLManager::createProjectile() {
    projectiles.push_back(*new Projectile(this->renderer, playerShip.pos, 12));
    std::cout << "Projectile created" << std::endl;
}

void SDLManager::createShip() {
    playerShip = *new Ship(this->getRenderer());
}

void SDLManager::createEnemies() {
    float initial_y = 40;
    int type = 1;
    for (int i = 0; i < 5; i++) {
        if (i == 0) type = 1;
        if (i == 1 || i == 2) type = 2;
        if (i == 3 || i == 4) type = 3;
        float initial_x = 80;
        std::vector<Enemy> v1;
        for (int j = 0; j < 12; j++) {
            Enemy e = Enemy(initial_x, initial_y, renderer, type);
            v1.push_back(e);
            e.~Enemy();
            initial_x += 45;
        }
        initial_y += 50;
        enemies.push_back(v1);
    }
    for (auto& row : enemies) {
        for (auto& enemy : row) {
            enemyMap.push_back(&enemy);
        }
    }
}

void SDLManager::moveEnemies() {
    bool temp = enemiesDirection;
    bool moveDown = false;
    for (int i = enemies.size() - 1; i >= 0; i--) {
        std::vector<Enemy> &row = enemies[i];
        for (Enemy &e: row) {
            if (e.position.x + 40 + 1 > enemies_x_end) {
                temp = false;
                moveDown = true;
                enemies_y += 10;
                break;
            }
            if (e.position.x - 1 < enemies_x) {
                temp = true;
                break;
            }
        }
    }
    enemiesDirection = temp;
    for (int i = enemies.size() - 1; i >= 0; i--) {
        std::vector<Enemy> &row = enemies[i];
        for (Enemy &e: row) {
            if (enemiesDirection) {
                e.moveRight();
            } else {
                e.moveLeft();
            }
            if (moveDown) {
                e.moveDown();
            }
        }
    }
}

bool SDLManager::checkCollision(Projectile *p) {
    const auto projectile_y = static_cast<float>( p->getRect()->y);
    const auto projectile_x = static_cast<float>( p->getRect()->x);
//    std::cout << "Projectile entered enemies range x = " << p->getRect()->x << " y = " << p->getRect()->y
//              << " enemies start x = " << enemies_x << " enemies end x = " << enemies_x + 50 * 12 << std::endl;
//    const auto index = floor((p->getRect()->x - enemies_x) / 50);
//    if (index < 0) return false;
    for (int i = enemies.size() - 1; i >= 0; i--) {
        std::vector<Enemy> &row = enemies[i];
        for (auto it = row.begin(); it != row.end(); ++it) {
            Enemy &enemy = *it;
            const Vector2f checker{enemy.position};
//            std::cout << " Checker y = " << checker.y << " bottom value = " << checker.y + 40 << " Checker x = "
//                      << checker.x << " checker x end = " << checker.x + 40 << std::endl;
            if ((checker.y < projectile_y && checker.y + 50 > projectile_y) &&
                (checker.x < projectile_x && checker.x + 40 > projectile_x)) {
                std::cout << " COLLISION " << std::endl;
                Enemy::increaseSpeed();
                enemy.~Enemy();
                row.erase(it);

                return true;
            }
        }
    }
    return false;

}

bool SDLManager::checkCollisionEnemyProjectile(Projectile *p) {
    const auto projectile_y = static_cast<float>( p->getRect()->y);
    const auto projectile_x = static_cast<float>( p->getRect()->x);
//    std::cout << "Projectile entered enemies range x = " << p->getRect()->x << " y = " << p->getRect()->y
//              << " enemies start x = " << enemies_x << " enemies end x = " << enemies_x + 50 * 12 << std::endl;
//    const auto index = floor((p->getRect()->x - enemies_x) / 50);
//    if (index < 0) return false;
    Vector2f checker = playerShip.pos;
    if ((checker.y < projectile_y && checker.y + 50 > projectile_y) &&
        (checker.x < projectile_x && checker.x + 40 > projectile_x)) {
        std::cout << " COLLISION " << std::endl;
        if(playersLives > 0){
            playerShip = Ship(renderer);
            playersLives--;
        }
        return true;
    }
    return false;

}



void SDLManager::fireEnemyProjectile() {
    auto currentTime = std::chrono::steady_clock::now();
    const std::chrono::duration<double> elapsed_seconds{currentTime - lastProjectile};
    const std::chrono::duration<double> duration{0.5};
    if (elapsed_seconds > duration) {
        int index = getRandomIndex();
        if (index == -1) {
            std::cout << "No enemies available to fire." << std::endl;
            return;
        }
        std::cout << "INDEX RANDOM " << index << " Enemy x = " << enemyMap[index]->position.x << " Enemy y = " << enemyMap[index]->position.y << std::endl;
        enemyProjectiles.push_back(*new Projectile(this->renderer, Vector2f(enemyMap[index]->position.x , enemyMap[index]->position.y + 60) , -12));
        lastProjectile = currentTime;
    }
}

int SDLManager::getRandomIndex() {
    // Ensure enemyMap is not empty
    if (enemyMap.empty()) {
        return -1; // or handle the empty case as needed
    }

    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the range
    std::uniform_int_distribution<> distr(0, enemyMap.size() - 1);

    return distr(gen);
}
