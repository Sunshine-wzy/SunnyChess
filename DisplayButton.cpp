#include "DisplayButton.h"
#include "graphics.h"


DisplayButton::DisplayButton(int x, int y)
            : Button("", x, y, 0, 0) {}

bool DisplayButton::isInside(int x, int y) {
    return false;
}


DisplayKeyButton::DisplayKeyButton(int x, int y) : DisplayButton(x, y), keySettings(nullptr) {}

void DisplayKeyButton::draw() {
    setcolor(WHITE);
    
    int length = 50;
    int offset = 10;
    
    rectangle(getX() - offset, getY() - offset, getX() + length - offset, getY() + length - offset);
    rectangle(getX() + length, getY(), getX() + length * 2, getY() + length);
    rectangle(getX(), getY() + length, getX() + length, getY() + length * 2);
    rectangle(getX() + length, getY() + length, getX() + length * 2, getY() + length * 2);
    rectangle(getX() + length * 2, getY() + length, getX() + length * 3, getY() + length * 2);
}
