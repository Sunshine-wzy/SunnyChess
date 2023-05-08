#include "GomokuMenu.h"
#include "MenuManager.h"
#include "RoundRectangleButton.h"
#include <iostream>

GomokuMenu::GomokuMenu() : board(GomokuChessBoard(10, 10, 700, 700)) {
    
}

void GomokuMenu::onInit() {
    board.draw();
    
    addButton(new RoundRectangleButton(MainMenu::WIDTH, MainMenu::HEIGHT / 2), [] {
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

void GomokuMenu::startGame() {
    
}

void GomokuMenu::runGame() {

}
