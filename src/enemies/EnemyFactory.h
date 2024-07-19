//
// Created by mrzardari on 7/18/24.
//

#ifndef SPACE_INVADERS_ENEMYFACTORY_H
#define SPACE_INVADERS_ENEMYFACTORY_H
#include <SDL2/SDL.h>
#include <string>

#include "Enemy.h"

class EnemyFactory {
        public:
            static Enemy createEnemy(const std::string& type, SDL_Renderer *renderer , float x , float y);

};


#endif //SPACE_INVADERS_ENEMYFACTORY_H
