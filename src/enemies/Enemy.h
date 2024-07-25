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
        static float speed;
        Enemy();
        Enemy(float x, float y, SDL_Renderer *renderer ,int type);
        virtual ~Enemy();
        virtual void moveRight();
        virtual void moveLeft();
        virtual  void moveDown();
        static void increaseSpeed();
        int type;
        Vector2f position;
        SDL_Texture * getTexture();

protected:
        SDL_Texture *texture;
};

#endif //SPACE_INVADERS_ENEMY_H
