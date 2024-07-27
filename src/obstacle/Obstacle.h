//
// Created by mrzardari on 7/28/24.
//

#ifndef SPACE_INVADERS_OBSTACLE_H
#define SPACE_INVADERS_OBSTACLE_H

#include <vector>


class Obstacle {
public:
    Obstacle(float x, float y);
    std::vector<std::vector<bool>> grid;
    float x;
    float y;

};


#endif //SPACE_INVADERS_OBSTACLE_H
