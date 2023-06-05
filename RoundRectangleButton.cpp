#include <graphics.h>
#include <utility>
#include "RoundRectangleButton.h"
#include "MenuManager.h"

RoundRectangleButton::RoundRectangleButton(std::string name, int x, int y, int width, int height, IMAGE *image, std::string text, int ellipseWidth, int ellipseHeight)
            : Button(std::move(name), x, y, width, height),
              image(image), text(std::move(text)),
              ellipseWidth(ellipseWidth), ellipseHeight(ellipseHeight),
              rect(RECT {x - width / 2, y - height / 2, x + width / 2, y + height / 2}) {}

void RoundRectangleButton::draw() {
    if (!isVisible()) return;
    
    setcolor(WHITE);
    setlinestyle(&MenuManager::main.getLineStyle());
    roundrect(rect.left, rect.top, rect.right, rect.bottom, ellipseWidth, ellipseHeight);

    if (image) {
        putimage(rect.left, rect.top, image);
    }
    
    if (!text.empty()) {
        settextstyle(30, 15, _T("Consolas"));
        setbkmode(TRANSPARENT);
        settextcolor(WHITE);
        drawtext(_T(text.c_str()), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);

        rectangle(rect.left, rect.top, rect.right, rect.bottom);
    }
}

bool RoundRectangleButton::isInside(int x, int y) {
    if (!Button::isInside(x, y)) return false;
    
    return x >= getX() - getWidth() / 2 && x <= getX() + getWidth() / 2
        && y >= getY() - getHeight() / 2 && y <= getY() + getHeight() / 2;
}

void RoundRectangleButton::setX(int x) {
    Button::setX(x);
    rect.left = x - getWidth() / 2;
    rect.right = x + getWidth() / 2;
}

void RoundRectangleButton::setY(int y) {
    Button::setY(y);
    rect.top = y - getHeight() / 2;
    rect.bottom = y + getHeight() / 2;
}

RoundRectangleButton::~RoundRectangleButton() = default;
