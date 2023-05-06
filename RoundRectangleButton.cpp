#include <graphics.h>
#include "RoundRectangleButton.h"

RoundRectangleButton::RoundRectangleButton(int x, int y, int width, int height, int ellipseWidth, int ellipseHeight) : Button(x, y, width, height), ellipseWidth(ellipseWidth), ellipseHeight(ellipseHeight) {}

void RoundRectangleButton::draw() {
    roundrect(getX() - getWidth() / 2, getY() - getHeight() / 2, getX() + getWidth() / 2, getY() + getHeight() / 2, ellipseWidth, ellipseHeight);
}
