#include "Menu.h"
#include <graphics.h>

Menu::Menu() = default;

Menu::~Menu() {
    deleteButtons();
}

void Menu::deleteButtons() {
    for (std::pair<Button *, ButtonAction> pair: buttons) {
        delete pair.first;
    }
    buttons.clear();
}

void Menu::open() {
    // 开始批量绘图
    BeginBatchDraw();

    // 清屏
    cleardevice();
    
    // 首次打开菜单初始化
    onOpenInit();
    
    // 初始化菜单
    onInit();

    // 初始化按钮
    deleteButtons();
    initButtons();

    // 绘制按钮
    drawButtons();

    // 结束批量绘图
    FlushBatchDraw();

    // 启动菜单
    onEnable();
}

void Menu::reopen() {
    // 开始批量绘图
    BeginBatchDraw();

    // 清屏
    cleardevice();

    // 初始化菜单
    onInit();

    // 绘制按钮
    drawButtons();

    // 结束批量绘图
    FlushBatchDraw();

    // 启动菜单
    onEnable();
}

void Menu::addButton(Button *button, ButtonAction action) {
    buttons.emplace_back(button, action);
}

void Menu::drawButtons() const {
    for (std::pair<Button *, ButtonAction> pair: buttons) {
        pair.first->draw();
    }
}

void Menu::clickButton(int x, int y) {
    for (std::pair<Button *, ButtonAction> pair: buttons) {
        if (pair.first->isInside(x, y)) {
            pair.second(*this, *pair.first, x, y);
            break;
        }
    }
}

void Menu::onOpenInit() {}

void Menu::onInit() {}

void Menu::initButtons() {}

void Menu::onEnable() {}
