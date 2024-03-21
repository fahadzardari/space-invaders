//
// Created by mrzardari on 3/21/24.
//

#include "Ship.h"

Ship::Ship(SDL_Renderer* renderer , ) {
    texture = IMG_LoadTexture(renderer , "../assets/ship.png");
    if(texture == NULL){
        std::cout << "Error Loading Texture Error: " << SDL_GetError() << std::endl;
    }
}

SDL_Texture *Ship::getTexture() {
    return texture;
}