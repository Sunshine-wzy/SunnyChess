#include "Menu.h"
#include <graphics.h>

Menu::Menu() = default;

Menu::~Menu() {
    for (std::pair<Button*, ButtonAction> pair : buttons) {
        delete pair.first;
    }
}

void Menu::open() {
    // 清屏
    cleardevice();

    // 初始化菜单
    onInit();

    // 初始化按钮
    initButtons();
    
    // 绘制按钮
    drawButtons();

    // 启动菜单
    onEnable();
}

void Menu::reopen() {
    // 清屏
    cleardevice();

    // 初始化菜单
    onInit();

    // 绘制按钮
    drawButtons();

    // 启动菜单
    onEnable();
}

void Menu::addButton(Button *button, ButtonAction action) {
    buttons.emplace_back(button, action);
}

void Menu::drawButtons() const {
    for (std::pair<Button*, ButtonAction> pair : buttons) {
        pair.first->draw();
    }
}

void Menu::clickButton(int x, int y) const {
    for (std::pair<Button*, ButtonAction> pair : buttons) {
        if (pair.first->isInside(x, y)) {
            pair.second();
            break;
        }
    }
}
