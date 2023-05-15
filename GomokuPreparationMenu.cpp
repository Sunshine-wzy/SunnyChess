#include "GomokuPreparationMenu.h"
#include "MenuManager.h"
#include "RoundRectangleButton.h"
#include "CircleSelectionButton.h"


GomokuPreparationMenu::GomokuPreparationMenu() = default;

void GomokuPreparationMenu::onInit() {

}

void GomokuPreparationMenu::initButtons() {
    addButton(
        new CircleSelectionButton(MainMenu::WIDTH / 2, MainMenu::HEIGHT / 2, 10),
        [](Menu &menu, Button &button, int x, int y) {
            auto &circleButton = dynamic_cast<CircleSelectionButton &>(button);
            circleButton.switchSelected();
            menu.reopen();
        }
    );

    addButton(
        new RoundRectangleButton(MainMenu::WIDTH, MainMenu::HEIGHT * 1 / 3, 100, 50),
        [](Menu &menu, Button &button, int x, int y) {
            MenuManager::gomoku.open();
        }
    );
    
    addButton(
        new RoundRectangleButton(MainMenu::WIDTH, MainMenu::HEIGHT * 2 / 3, 100, 50),
        [](Menu &menu, Button &button, int x, int y) {
            MenuManager::main.open();
        }
    );
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
