//
// Created by mrzardari on 7/18/24.
//

#include "Enemy.h"

float Enemy::speed = 1;

Enemy::Enemy() {}

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
    speed += 0.1;
}

Enemy::~Enemy() = default;
