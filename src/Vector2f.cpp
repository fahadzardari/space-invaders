//
// Created by mrzardari on 3/21/24.
//

#include "Vector2f.h"

Vector2f::Vector2f() {
    x = 0.0f;
    y = 0.0f;
}

Vector2f::Vector2f(float x_val, float y_val) : x(x_val) , y(y_val) {}

void Vector2f::add(float x_val, float y_val) {
    x += x_val;
    y += y_val;
}
