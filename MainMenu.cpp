#include "MainMenu.h"
#include "MenuManager.h"
#include "RoundRectangleButton.h"

MainMenu::MainMenu() {
    lineStyle.style = PS_SOLID;
    lineStyle.thickness = 3;
}

void MainMenu::onInit() {
    // 设置线条样式
    setlinestyle(&getLineStyle());

    // 绘制背景
	loadimage(nullptr, "../resources/main_menu_background.png", WIDTH, HEIGHT);
}

void MainMenu::initButtons() {
    // 五子棋
    addButton(
        new RoundRectangleButton("gomoku_preparation", WIDTH / 2, HEIGHT / 4 * 3),
        [](Menu &menu, Button &button, int x, int y) {
            MenuManager::gomokuPreparation.open();
        }
    );
}

void MainMenu::onEnable() {
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


LINESTYLE &MainMenu::getLineStyle() {
    return lineStyle;
}
