#include <graphics.h>
#include <utility>
#include "RoundRectangleButton.h"
#include "MenuManager.h"

RoundRectangleButton::RoundRectangleButton(std::string name, int x, int y, int width, int height, int ellipseWidth, int ellipseHeight)
        : Button(std::move(name), x, y, width, height), ellipseWidth(ellipseWidth), ellipseHeight(ellipseHeight) {}

void RoundRectangleButton::draw() {
    setcolor(WHITE);
    setlinestyle(&MenuManager::main.getLineStyle());
    roundrect(getX() - getWidth() / 2, getY() - getHeight() / 2, getX() + getWidth() / 2, getY() + getHeight() / 2, ellipseWidth, ellipseHeight);
}

bool RoundRectangleButton::isInside(int x, int y) {
    return x >= getX() - getWidth() / 2 && x <= getX() + getWidth() / 2
        && y >= getY() - getHeight() / 2 && y <= getY() + getHeight() / 2;
}

RoundRectangleButton::~RoundRectangleButton() = default;
