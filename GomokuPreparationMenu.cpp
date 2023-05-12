#include "GomokuPreparationMenu.h"
#include "MenuManager.h"
#include "RoundRectangleButton.h"


GomokuPreparationMenu::GomokuPreparationMenu() = default;

void GomokuPreparationMenu::onInit() {
    
}

void GomokuPreparationMenu::initButtons() {
    addButton(new RoundRectangleButton(MainMenu::WIDTH, MainMenu::HEIGHT * 1 / 3, 100, 50), [] {
        MenuManager::gomoku.open();
    });

    addButton(new RoundRectangleButton(MainMenu::WIDTH, MainMenu::HEIGHT * 2 / 3, 100, 50), [] {
        MenuManager::main.open();
    });
}

void GomokuPreparationMenu::onEnable() {
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
