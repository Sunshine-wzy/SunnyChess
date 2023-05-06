#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu() {
    lineStyle.style = PS_SOLID;
    lineStyle.thickness = 3;
}

void MainMenu::init() {
    // 初始化图形模式
    initgraph(WIDTH, HEIGHT);
    
    // 设置线条样式
    setlinestyle(&getLineStyle());
    
    // 绘制按钮
    drawButtons();
    
    // 消息处理
    flushmessage();
    while (true) {
        ExMessage message = getmessage();
        switch (message.message) {
            // 鼠标左键弹起
            case WM_LBUTTONUP:
                std::cout << "LBUTTONUP" << std::endl;
                break;
        }
    }
}

void MainMenu::drawButtons() {
    drawSelectingButton(WIDTH / 4, HEIGHT / 4 * 3);
    drawSelectingButton(WIDTH / 4 * 3, HEIGHT / 4 * 3);
}

void MainMenu::drawSelectingButton(int x, int y) {
    
}

LINESTYLE &MainMenu::getLineStyle() {
    return lineStyle;
}