#include "MainMenu.h"
#include "MenuManager.h"
#include "RoundRectangleButton.h"
#include <iostream>

MainMenu::MainMenu() {
    lineStyle.style = PS_SOLID;
    lineStyle.thickness = 3;
}

void MainMenu::onInit() {
    // 设置线条样式
    setlinestyle(&getLineStyle());

    // 绘制背景
	loadimage(nullptr, "../resources/chesspan.png", 100, 100);
 
    // 设置按钮
    setButtons();
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

void MainMenu::setButtons() {
    addButton(new RoundRectangleButton(WIDTH / 4, HEIGHT / 4 * 3), [] {
        std::cout << "b1" << std::endl;
        MenuManager::gomoku.open();
    });

    addButton(new RoundRectangleButton(WIDTH / 4 * 3, HEIGHT / 4 * 3), [] {
        std::cout << "b2" << std::endl;
    });

    
}

LINESTYLE &MainMenu::getLineStyle() {
    return lineStyle;
}
