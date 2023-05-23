#include "Direction.h"

Direction::Direction(int offsetX, int offsetY) : offsetX(offsetX), offsetY(offsetY) {}

int Direction::getOffsetX() const {
    return offsetX;
}

int Direction::getOffsetY() const {
    return offsetY;
}

Direction Direction::right = Direction(1, 0);

Direction Direction::left = Direction(-1, 0);

Direction Direction::up = Direction(0, 1);

Direction Direction::down = Direction(0, -1);

Direction Direction::upRight = Direction(1, 1);

Direction Direction::downLeft = Direction(-1, -1);

Direction Direction::upLeft = Direction(-1, 1);

Direction Direction::downRight = Direction(1, -1);
