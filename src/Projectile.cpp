//
// Created by mrzardari on 3/29/24.
//

#include "Projectile.h"
Projectile::Projectile(SDL_Renderer* renderer, Vector2f shipPos) {
    rect.x = static_cast<int>(shipPos.x + 25) ;
    rect.y = static_cast<int>(shipPos.y - 25);
    rect.w = 2;
    rect.h = 25;

}

void Projectile::updatePosition() {
    if(rect.y < 10) {
        this->~Projectile();
    }
    rect.y -= 12;
    std::cout << "New Position y value is = " << rect.y << std::endl;
}

const SDL_Rect * Projectile::getRect() {
    return &this->rect;
}

Projectile::~Projectile() = default;
