//
// Created by mrzardari on 3/29/24.
//

#include "Projectile.h"
#include "Constants.h"
Projectile::Projectile(SDL_Renderer* renderer, Vector2f shipPos ,int spd) {
    rect.x = static_cast<int>(shipPos.x + 20) ;
    rect.y = static_cast<int>(shipPos.y - 20);
    rect.w = 2;
    rect.h = 20;
    speed = spd;

}

void Projectile::updatePosition() {
    if(rect.y < 10) {
        this->~Projectile();
    }
    if(rect.y > SCREEN_HEIGHT){
        this->~Projectile();
    }
    rect.y -= speed;
//    std::cout << "New Position y value is = " << rect.y << std::endl;
}

const SDL_Rect * Projectile::getRect() {
    return &this->rect;
}

Projectile::~Projectile() = default;
