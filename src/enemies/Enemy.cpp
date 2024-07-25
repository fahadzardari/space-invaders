//
// Created by mrzardari on 7/18/24.
//

#include "Enemy.h"


Enemy::Enemy() {}
Enemy::Enemy(float x, float y, SDL_Renderer *renderer , int type) {
    if(type == 1) texture = IMG_LoadTexture(renderer , "../assets/invader_purple.png");
    if(type == 2) texture = IMG_LoadTexture(renderer , "../assets/invader_white.png");
    if(type == 3) texture = IMG_LoadTexture(renderer , "../assets/invader_green.png");
    position = Vector2f(x , y);
    if(texture == NULL){
        std::cout << "Error Loading Texture Error: " << SDL_GetError() << std::endl;
    }
}
float Enemy::speed = 1;


SDL_Texture * Enemy::getTexture(){
    return texture;
}

void Enemy::moveRight() {
    position.x += speed;
}

void Enemy::moveLeft() {
    position.x -= speed;

}

void Enemy::moveDown() {
    position.y += 10;
}

void Enemy::increaseSpeed() {
    speed += 0.05;
}

Enemy::~Enemy() = default;
