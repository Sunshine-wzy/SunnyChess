//
// Created by 11235 on 2023/5/6.
//

#include "Button.h"

Button::Button(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

int Button::getX() const {
    return x;
}

int Button::getY() const {
    return y;
}

int Button::getWidth() const {
    return width;
}

int Button::getHeight() const {
    return height;
}

Button::~Button() = default;
