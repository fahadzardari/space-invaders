//
// Created by mrzardari on 3/21/24.
//

#include "Ship.h"

Ship::Ship(SDL_Renderer* renderer) {
    texture = IMG_LoadTexture(renderer , "../assets/ship.png");
    pos = Vector2f(static_cast<float> (SCREEN_WIDTH / 2) , static_cast<float> (SCREEN_HEIGHT - 75) );
    if(texture == NULL){
        std::cout << "Error Loading Texture Error: " << SDL_GetError() << std::endl;
    }
}

SDL_Texture *Ship::getTexture() {
    return texture;
}

void Ship::moveRight() {
        if(pos.x == SCREEN_WIDTH - 50){
            return;
        }
        pos.add(5 , 0);
}

void Ship::moveLeft() {
    if(pos.x == 0){
        return;
    }
    pos.add(-5 , 0);
}
