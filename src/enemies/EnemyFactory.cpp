//
// Created by mrzardari on 7/18/24.
//

#include "EnemyFactory.h"
#include "Invader.h"


Enemy EnemyFactory::createEnemy(const std::string& type, SDL_Renderer *renderer, float x, float y) {
    if(type == "invader"){
        std::cout << "Created invader class";
        return Invader(x , y , renderer);
    }

    return {};
}
