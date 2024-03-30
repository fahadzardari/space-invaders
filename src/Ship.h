//
// Created by mrzardari on 3/21/24.
//

#ifndef SPACE_INVADERS_SHIP_H
#define SPACE_INVADERS_SHIP_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Vector2f.h"
#include "Constants.h"


class Ship {
    public:
        Ship();
        Ship(SDL_Renderer* renderer);
        SDL_Texture* getTexture();
        Vector2f pos;
        void moveRight();
        void moveLeft();
    private:
        SDL_Texture * texture;
};


#endif //SPACE_INVADERS_SHIP_H
