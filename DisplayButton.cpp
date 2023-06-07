#include "DisplayButton.h"
#include "graphics.h"


DisplayButton::DisplayButton(int x, int y)
            : Button("", x, y, 0, 0) {}

bool DisplayButton::isInside(int x, int y) {
    return false;
}


DisplayKeyButton::DisplayKeyButton(int x, int y) : DisplayButton(x, y), keySettings(nullptr) {}

void DisplayKeyButton::draw() {
    if (keySettings) {
        setcolor(BLACK);

        int length = 50;
        int offset = 10;

        RECT rectQ = {getX() - offset, getY() - offset, getX() + length - offset, getY() + length - offset};
        RECT rectW = {getX() + length, getY(), getX() + length * 2, getY() + length};
        RECT rectA = {getX(), getY() + length, getX() + length, getY() + length * 2};
        RECT rectS = {getX() + length, getY() + length, getX() + length * 2, getY() + length * 2};
        RECT rectD = {getX() + length * 2, getY() + length, getX() + length * 3, getY() + length * 2};

        rectangle(rectQ.left, rectQ.top, rectQ.right, rectQ.bottom);
        rectangle(rectW.left, rectW.top, rectW.right, rectW.bottom);
        rectangle(rectA.left, rectA.top, rectA.right, rectA.bottom);
        rectangle(rectS.left, rectS.top, rectS.right, rectS.bottom);
        rectangle(rectD.left, rectD.top, rectD.right, rectD.bottom);
        
        settextstyle(30, 20, _T("Consolas"));
        setbkmode(TRANSPARENT);
        settextcolor(BLACK);
        drawtext(keySettings->keys[4].c_str(), &rectQ, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        
        if (keySettings->up == VK_UP) {
            settextstyle(25, 10, _T("Consolas"));
        }
        drawtext(keySettings->keys[3].c_str(), &rectD, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        drawtext(keySettings->keys[2].c_str(), &rectA, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        drawtext(keySettings->keys[1].c_str(), &rectS, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        drawtext(keySettings->keys[0].c_str(), &rectW, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }
}

void DisplayKeyButton::setKeySettings(const KeySettings *settings) {
    keySettings = settings;
}
