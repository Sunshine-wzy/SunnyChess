#include "Button.h"
#include <utility>

Button::Button(std::string name, int x, int y, int width, int height) : name(std::move(name)), x(x), y(y), width(width), height(height) {}

const std::string &Button::getName() const {
    return name;
}

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
