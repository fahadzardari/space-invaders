//
// Created by mrzardari on 3/21/24.
//

#ifndef SPACE_INVADERS_VECTOR2F_H
#define SPACE_INVADERS_VECTOR2F_H


class Vector2f {
    public:
        Vector2f();
        Vector2f(float x_val , float y_val);
        void add(float x_val , float y_val);
        void add(Vector2f v);
        float x;
        float y;
};


#endif //SPACE_INVADERS_VECTOR2F_H
