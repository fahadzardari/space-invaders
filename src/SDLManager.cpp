//
// Created by mrzardari on 3/1/24.
//

#include "SDLManager.h"


SDL_Renderer *getRenderer();

SDLManager::SDLManager() {
    lastProjectile = std::chrono::steady_clock::now();
};

void SDLManager::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "Initialization Error for SDL" << SDL_GetError() << std::endl;
    if (!IMG_Init(IMG_INIT_PNG))
        std::cout << "Initialization Error for SDL IMAGE" << SDL_GetError() << std::endl;
    initializeFont();
    this->enemies_x = 80;
    this->enemies_x_end = 720;
    this->enemies_y = 240;
    this->enemiesDirection = true;
    this->playersLives = 3;
    this->highestScore = 0;
    this->currentScore = 0;
    this->gameState = 0;
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

void SDLManager::renderTexture(SDL_Texture *tex, SDL_Rect dest) {
    SDL_RenderCopy(this->renderer, tex, nullptr, &dest);
}

void SDLManager::clear() {
    SDL_RenderClear(this->renderer);
}

void SDLManager::render() {
    renderFont();
    if (gameState == 0) {
        startScreen();
    }
    if (gameState == 1) {
        renderPlayerLives();
        moveEnemies();
        fireEnemyProjectile();
        renderEnemies();
        renderObstacles();
        if (playersLives > 0) renderShip(&playerShip);
        renderProjectiles();
        if(enemies[enemies.size() - 1][0].position.y >= OBSTACLE_Y) gameState = 2;
    }
    if (gameState == 2) {
        gameOverScreen();
    }
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
    SDL_RenderCopy(this->renderer, ship->getTexture(), nullptr, &dest);
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
        if (checkCollisionWithBunker(&p)) {
            p.~Projectile();
            it = projectiles.erase(it);
            continue;
        }
        if (checkCollision(&p)) {
            p.~Projectile();
            it = projectiles.erase(it);
            continue;
        }

        if (p.getRect()->y < 80) {
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
        if (checkCollisionWithBunker(&p)) {
            p.~Projectile();
            it = enemyProjectiles.erase(it);
            continue;
        }
        if (p.getRect()->y > 100) {
            if (checkCollisionEnemyProjectile(&p)) {
                p.~Projectile();
                it = enemyProjectiles.erase(it);
                continue;
            }
        }
        if (p.getRect()->y > SCREEN_HEIGHT - 80) {
            p.~Projectile();
            it = enemyProjectiles.erase(it);
        } else {
            it++;
        }
    }
}

void SDLManager::createProjectile() {
    projectiles.push_back(*new Projectile(this->renderer, playerShip.pos, 8));
    std::cout << "Projectile created" << std::endl;
}

void SDLManager::createShip() {
    playerShip = *new Ship(this->getRenderer());
}

void SDLManager::createEnemies() {
    float initial_y = 180;
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
}

void SDLManager::createObstacles() {
    float initial_x = OBSTACLE_X;
    float initial_y = OBSTACLE_Y;
    for (int i = 0; i < 4; i++) {
        obstacles.emplace_back(initial_x, initial_y);
        initial_x += OBSTACLE_RANGE;
    }
}

void SDLManager::renderObstacles() {
    for (auto &obstacle: obstacles) {
        float y = obstacle.y;
        for (const auto &j: obstacle.grid) {
            float x = obstacle.x;
            for (bool k: j) {
                if (k) {
                    renderBlock(SDL_Rect(x, y, GRID_SQUARE_WIDTH, GRID_SQUARE_WIDTH));
                }
                x += GRID_SQUARE_WIDTH;
            }
            y += GRID_SQUARE_WIDTH;
        }
    }
}

void SDLManager::renderBlock(SDL_Rect rect) {
    SDL_SetRenderDrawColor(renderer, 19, 157, 8, 1);
    SDL_RenderFillRect(renderer, &rect);
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
    for (int i = enemies.size() - 1; i >= 0; i--) {
        std::vector<Enemy> &row = enemies[i];
        for (auto it = row.begin(); it != row.end(); ++it) {
            Enemy &enemy = *it;
            const Vector2f checker{enemy.position};
            if ((checker.y < projectile_y && checker.y + 50 > projectile_y) &&
                (checker.x < projectile_x && checker.x + 40 > projectile_x)) {
                Enemy::increaseSpeed();
                this->updateScore(enemy.type);
                enemy.~Enemy();
                row.erase(it);
                if (row.empty()) {
                    enemies.erase(enemies.begin() + i);
                }
                if (enemies.empty()) {
                    gameState = 2;
                    if (highestScore < currentScore) {
                        highestScore = currentScore;
                    }
                }
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
        if (playersLives > 0) {
            playerShip = Ship(renderer);
            playersLives--;
        }
        if (playersLives == 0) {
            gameState = 2;
            if (highestScore < currentScore) {
                highestScore = currentScore;
            }
        }
        return true;
    }
    return false;

}

bool SDLManager::checkCollisionWithBunker(Projectile *p) {
    int obstacles_width = obstacles[0].grid[0].size();
    int obstacles_height = obstacles[0].grid.size();
    int initial_x = 100;
    int x = p->getRect()->x;
    int y = p->getRect()->y + 8;
    if (y > OBSTACLE_Y - 100 && y < OBSTACLE_Y + obstacles_height * GRID_SQUARE_WIDTH) {
        int obstacle_range = std::floor((x - initial_x) / OBSTACLE_RANGE);
        int low_limit = obstacle_range * OBSTACLE_RANGE + OBSTACLE_X;
        int high_limit = low_limit + obstacles_width * GRID_SQUARE_WIDTH;
        if (x > low_limit && x < high_limit) {
            int col = std::floor((x - low_limit) / GRID_SQUARE_WIDTH);
            int row = std::floor((y - OBSTACLE_Y) / GRID_SQUARE_WIDTH);
            int oby = OBSTACLE_Y;
            std::cout << " Row = " << y - OBSTACLE_Y << " Col = " << col << std::endl;
            std::cout << " Y = " << y << " OBSTACLE_Y = " << OBSTACLE_Y << std::endl;
            if(row < 0) return false;
            if (obstacles[obstacle_range].grid[row][col]) {
                obstacles[obstacle_range].grid[row][col] = false;
                if(row > 0) obstacles[obstacle_range].grid[row-1][col] = false;
                if(row < obstacles_height - 1) obstacles[obstacle_range].grid[row+1][col] = false;
                if(col > 0) {
                    obstacles[obstacle_range].grid[row][col - 1] = false;
                    if(row < obstacles_height - 1) obstacles[obstacle_range].grid[row+1][col-1] = false;
                    if(row > 0) obstacles[obstacle_range].grid[row-1][col-1] = false;
                }
                if(col < obstacles_width - 1) {
                    obstacles[obstacle_range].grid[row][col + 1] = false;
                    if(row < obstacles_height - 1) obstacles[obstacle_range].grid[row+1][col+1] = false;
                    if(row > 0) obstacles[obstacle_range].grid[row-1][col+1] = false;
                }
                return true;
            }
        }
    }
    return false;
}

void SDLManager::fireEnemyProjectile() {
    auto currentTime = std::chrono::steady_clock::now();
    const std::chrono::duration<double> elapsed_seconds{currentTime - lastProjectile};
    const std::chrono::duration<double> duration{0.6};
    if (elapsed_seconds > duration && !enemies.empty()) {
        int row = getRandomIndex(enemies.size());
        while (enemies[row].empty()) {
            row = getRandomIndex(enemies.size());
        }
        int column = getRandomIndex(enemies[row].size());

        enemyProjectiles.push_back(
                *new Projectile(this->renderer,
                                Vector2f(enemies[row][column].position.x, enemies[row][column].position.y + 60),
                                -8));
        lastProjectile = currentTime;
    }
}

int SDLManager::getRandomIndex(int size) {
    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the range
    std::uniform_int_distribution<> distr(0, size - 1);

    return distr(gen);
}

void SDLManager::renderPlayerLives() {
    SDL_Texture *tex = IMG_LoadTexture(getRenderer(), "../assets/ship-fancy.png");
    SDL_Rect dest(80, SCREEN_HEIGHT - 60, 40, 40);
    for (int i = 0; i < playersLives; i++) {
        SDL_RenderCopy(this->renderer, tex, nullptr, &dest);
        dest.x += 60;
    }
    SDL_Rect line(80, SCREEN_HEIGHT - 70, SCREEN_WIDTH - 160, 2);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &line);
    SDL_DestroyTexture(tex);
}

void SDLManager::initializeFont() {
    if (TTF_Init() == -1) {
        std::cout << "Could not initialize SDL2_ttf, error: " << TTF_GetError() << std::endl;
    } else {
        std::cout << "SDL2_ttf system ready to go!" << std::endl;
    }
    font = TTF_OpenFont(FONT_AMATIC, 100);
    // Confirm that it was loaded
    if (font == nullptr) {
        std::cout << "Could not load font" << std::endl;
        exit(1);
    }
}

void SDLManager::renderFont() {
    std::string text =
            "Current Score : " + std::to_string(currentScore) + " Highest Score: " + std::to_string(highestScore);
    renderText(text, 80, 10, SCREEN_WIDTH - 160);
}

void SDLManager::updateScore(int type) {
    if (type == 3) this->currentScore += 10;
    if (type == 2) this->currentScore += 20;
    if (type == 1) this->currentScore += 30;
}

void SDLManager::startScreen() {
    int baseX = SCREEN_WIDTH / 2 - (SCREEN_WIDTH - 360) / 2;
    int baseY = SCREEN_HEIGHT / 3;
    int baseW = SCREEN_WIDTH - 360;
    std::string text =
            "PRESS P TO PLAY";
    renderText(text, baseX, baseY, baseW);
    text = "SPACE INVADERS";
    renderText(text, baseX += 20, baseY += 60, baseW -= 40);
    text = " 30 POINTS";
    renderText(text, baseX += 50, baseY += 60, baseW -= 80);
    renderTexture(loadTexture("../assets/invader_purple.png"), SDL_Rect(baseX - 30, baseY + 5, 40, 40));
    text = " 20 POINTS";
    renderText(text, baseX, baseY += 60, baseW);
    renderTexture(loadTexture("../assets/invader_white.png"), SDL_Rect(baseX - 30, baseY + 5, 40, 40));
    text = " 10 POINTS";
    renderText(text, baseX, baseY += 60, baseW);
    renderTexture(loadTexture("../assets/invader_green.png"), SDL_Rect(baseX - 30, baseY + 5, 40, 40));
}

void SDLManager::gameOverScreen() {
    int baseX = SCREEN_WIDTH / 2 - (SCREEN_WIDTH - 360) / 2;
    int baseY = SCREEN_HEIGHT / 3;
    int baseW = SCREEN_WIDTH - 360;
    std::string text =
            "GAME OVER!";
    renderText(text, baseX, baseY, baseW);
    text =
            "PRESS R TO RESTART";
    renderText(text, baseX, baseY += baseY / 2, baseW);
}

void SDLManager::restart() {
    enemies.clear();
    projectiles.clear();
    enemyProjectiles.clear();
    obstacles.clear();
    enemies.shrink_to_fit();
    projectiles.shrink_to_fit();
    enemyProjectiles.shrink_to_fit();
    obstacles.shrink_to_fit();
    this->enemies_x = 80;
    this->enemies_x_end = 720;
    this->enemies_y = 240;
    this->enemiesDirection = true;
    this->playersLives = 3;
    this->currentScore = 0;
    Enemy::speed = 1;
    createShip();
    createEnemies();
    createObstacles();
}

void SDLManager::renderText(const std::string &text, int x, int y, int w) {
    SDL_Surface *surfaceText = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255});
    SDL_Texture *textureText = SDL_CreateTextureFromSurface(renderer, surfaceText);
    SDL_Rect rectangle = {x, y, w, 50};
    SDL_RenderCopy(renderer, textureText, nullptr, &rectangle);
    SDL_FreeSurface(surfaceText);
    SDL_DestroyTexture(textureText);
}

