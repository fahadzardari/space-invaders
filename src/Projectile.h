//
// Created by mrzardari on 3/29/24.
//

#ifndef SPACE_INVADERS_PROJECTILE_H
#define SPACE_INVADERS_PROJECTILE_H
#include <SDL2/SDL.h>
#include "Vector2f.h"
#include <iostream>


class Projectile {
public:
    Projectile(SDL_Renderer* renderer , Vector2f shipPos);
    virtual ~Projectile();
    const SDL_Rect * getRect();
    void updatePosition();
private:
    SDL_Rect rect;
};


#endif //SPACE_INVADERS_PROJECTILE_H
