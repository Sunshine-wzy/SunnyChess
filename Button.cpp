#include "Button.h"
#include <utility>

Button::Button(std::string name, int x, int y, int width, int height)
            : name(std::move(name)), x(x), y(y),
              width(width), height(height), visible(true),
              visibleCount(0), currentVisibleCount(0) {}

const std::string &Button::getName() const {
    return name;
}

int Button::getX() const {
    return x;
}

int Button::getY() const {
    return y;
}

void Button::setX(int x) {
    Button::x = x;
}

void Button::setY(int y) {
    Button::y = y;
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
    if (isVisible) {
        // 保证线程安全
        const std::lock_guard<std::mutex> lock(mutexVisibleCountDown);
        
        currentVisibleCount = visibleCount;
    }
}

bool Button::isInside(int x, int y) {
    return visible;
}

int Button::getVisibleCount() const {
    return visibleCount;
}

void Button::setVisibleCount(int count) {
    visibleCount = count;
}

int Button::visibleCountDown() {
    // 保证线程安全
    const std::lock_guard<std::mutex> lock(mutexVisibleCountDown);
    
    if (currentVisibleCount > 0) {
        currentVisibleCount--;
    } else {
        setVisible(false);
    }
    return currentVisibleCount;
}

Button::~Button() = default;
