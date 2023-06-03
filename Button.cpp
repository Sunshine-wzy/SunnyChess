#include "Button.h"
#include <utility>

Button::Button(std::string name, int x, int y, int width, int height)
            : name(std::move(name)), x(x), y(y),
              width(width), height(height), visible(true) {}

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

bool Button::isVisible() const {
    return visible;
}

void Button::setVisible(bool isVisible) {
    visible = isVisible;
}

bool Button::isInside(int x, int y) {
    return visible;
}

Button::~Button() = default;
