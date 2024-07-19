//
// Created by mrzardari on 7/18/24.
//

#ifndef SPACE_INVADERS_ENEMY_H
#define SPACE_INVADERS_ENEMY_H

#include "../Vector2f.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <SDL_image.h>


class Enemy{
    public:
        Enemy();
        virtual void moveRight();
        virtual void moveLeft();
        Vector2f position;
        SDL_Texture * getTexture();

protected:
        SDL_Texture *texture;
};

#endif //SPACE_INVADERS_ENEMY_H
