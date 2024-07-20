//
// Created by mrzardari on 7/18/24.
//

#include "Invader.h"


Invader::Invader(float x, float y, SDL_Renderer *renderer) {
        texture = IMG_LoadTexture(renderer , "../assets/invader_white.png");
        position = Vector2f(x , y);
        if(texture == NULL){
         std::cout << "Error Loading Texture Error: " << SDL_GetError() << std::endl;
        }
}

void Invader::moveRight()  {
     position.x += 4;
}

void Invader::moveLeft()  {
    position.x -= 4;
}
