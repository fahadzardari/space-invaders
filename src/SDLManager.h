//
// Created by mrzardari on 3/1/24.
//

#ifndef SPACE_INVADERS_SDLMANAGER_H
#define SPACE_INVADERS_SDLMANAGER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keyboard.h>
#include <iostream>
#include <vector>
#include "Constants.h"
#include "Ship.h"
#include "Projectile.h"
#include "enemies/Enemy.h"
#include "enemies/EnemyFactory.h"
#include <cmath>
#include <chrono>
#include <unordered_map>
#include <cmath>
#include <random>
#include <SDL2/SDL_ttf.h>
//#include FT_FREETYPE_H

class SDLManager {
public:
    SDLManager();
    void initialize();
    void createWindow();
    void createProjectile();
    void createShip();
    SDL_Texture* loadTexture(const char* filePath);
    SDL_Renderer* getRenderer();
    void display();
    void renderTexture(SDL_Texture* tex);
    void renderProjectiles();
    void renderEnemies();
    void renderShip(Ship* ship);
    void clear();
    void cleanup();
    void render();
    Ship playerShip;
    void createEnemies();
    void moveEnemies();
    void initializeFont();
    bool enemiesDirection;
    Enemy enemy;
    void renderEnemy(Enemy *enemy);
    bool checkCollision(Projectile *p);
    bool checkCollisionEnemyProjectile(Projectile *p);
    float enemies_x ;
    float enemies_x_end;
    float enemies_y ;
    std::chrono::time_point<std::chrono::steady_clock> lastProjectile;
    void fireEnemyProjectile();
    static int getRandomIndex(int size);
    int playersLives;
    int currentScore;
    int highestScore;
    TTF_Font *font;
    void renderFont();
    void renderPlayerLives();
    void updateScore(int type);
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    std::vector<Projectile> projectiles;
    std::vector<std::vector<Enemy>> enemies;
    std::vector<Projectile> enemyProjectiles;
};


#endif //SPACE_INVADERS_SDLMANAGER_H
