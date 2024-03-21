//
// Created by mrzardari on 3/21/24.
//

#ifndef SPACE_INVADERS_SHIP_H
#define SPACE_INVADERS_SHIP_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Vector2f.h"


class Ship {
    public:
        Ship(SDL_Renderer* renderer);
        SDL_Texture* getTexture();
    private:
        SDL_Texture * texture;
        Vector2f pos;
};


#endif //SPACE_INVADERS_SHIP_H
