//
// Created by mrzardari on 3/21/24.
//

#include "Ship.h"

Ship::Ship() = default;

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
        std::cout<<"x= " << pos.x << std::endl;
        if(pos.x >= SCREEN_WIDTH - 120){
            std::cout<<"limit reached";
            return;
        }
        pos.add(8 , 0);
}

void Ship::moveLeft() {
    std::cout<<"x= " << pos.x << std::endl;
    if(pos.x <= 80){
        return;
    }
    pos.add(-8 , 0);
}
