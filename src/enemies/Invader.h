//
// Created by mrzardari on 7/18/24.
//

#ifndef SPACE_INVADERS_INVADER_H
#define SPACE_INVADERS_INVADER_H

#include "Enemy.h"

class Invader : public Enemy {
public:
    Invader(float x , float y , SDL_Renderer *renderer);
    void moveRight() override;
    void moveLeft() override;


};


#endif //SPACE_INVADERS_INVADER_H
