#include "CircleSelectionButton.h"
#include "MenuManager.h"
#include <utility>


CircleSelectionButton::CircleSelectionButton(std::string name, int x, int y, int radius, RECT relativeRect, IMAGE *image, std::string text)
        : SelectionButton(std::move(name), x, y, radius * 2, radius * 2),
          radius(radius), relativeRect(relativeRect), image(image), text(std::move(text)),
          realRect(RECT {getX() + relativeRect.left, getY() + relativeRect.top, getX() + relativeRect.right, getY() + relativeRect.bottom}) {}

CircleSelectionButton::~CircleSelectionButton() {
    delete image;
}

bool CircleSelectionButton::isInside(int x, int y) {
    if (!Button::isInside(x, y)) return false;
    
    return (x >= realRect.left && x <= realRect.right && y >= realRect.top && y <= realRect.bottom) || ((x - getX()) * (x - getX()) + (y - getY()) * (y - getY()) <= radius * radius);
}

void CircleSelectionButton::drawNormal() {
    setlinestyle(&MenuManager::main.getLineStyle());
    setfillcolor(WHITE);
    solidcircle(getX(), getY(), radius);

    if (image) {
        putimage(realRect.left, realRect.top, image);
    }
    
    if (!text.empty()) {
        settextstyle(30, 15, _T("Consolas"));
        setbkmode(TRANSPARENT);
        settextcolor(BLACK);
        drawtext(_T(text.c_str()), &realRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);

        rectangle(realRect.left, realRect.top, realRect.right, realRect.bottom);
    }
}

void CircleSelectionButton::drawSelected() {
    drawNormal();
    
    setfillcolor(GREEN);
    solidcircle(getX(), getY(), radius * 3 / 5);
}
