#include "CircleSelectionButton.h"
#include <graphics.h>


CircleSelectionButton::CircleSelectionButton(int x, int y, int radius)
        : SelectionButton(x, y, radius * 2, radius * 2), radius(radius) {}

bool CircleSelectionButton::isInside(int x, int y) {
    return (x - getX()) * (x - getX()) + (y - getY()) * (y - getY()) <= radius * radius;
}

void CircleSelectionButton::drawNormal() {
    setcolor(WHITE);
    solidcircle(getX(), getY(), radius);
}

void CircleSelectionButton::drawSelected() {
    setcolor(WHITE);
    solidcircle(getX(), getY(), radius);
    setcolor(GREEN);
    solidcircle(getX(), getY(), radius * 3 / 4);
}
