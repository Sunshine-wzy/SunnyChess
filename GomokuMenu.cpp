#include "GomokuMenu.h"
#include "MenuManager.h"
#include "RoundRectangleButton.h"
#include <iostream>

GomokuMenu::GomokuMenu() = default;

void GomokuMenu::onInit() {
    addButton(new RoundRectangleButton(MainMenu::WIDTH / 2, MainMenu::HEIGHT / 2), [] {
        std::cout << "b3" << std::endl;
        MenuManager::main.open();
    });
}

void GomokuMenu::onEnable() {
    // 消息处理
    flushmessage();
    while (true) {
        ExMessage message = getmessage();
        switch (message.message) {
            // 鼠标左键弹起
            case WM_LBUTTONUP:
                clickButton(message.x, message.y);
                break;
        }
    }
}
