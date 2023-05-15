#include "GomokuMenu.h"
#include "MenuManager.h"
#include "RoundRectangleButton.h"
#include <cstdio>

GomokuMenu::GomokuMenu() : board(GomokuChessBoard(10, 10, 700, 700, 19)) {
    
}

void GomokuMenu::onInit() {
    board.draw();
}

void GomokuMenu::initButtons() {
    addButton(
        new RoundRectangleButton("gomoku_preparation", MainMenu::WIDTH, MainMenu::HEIGHT / 2, 100, 50),
        [](Menu &menu, Button &button, int x, int y) {
            MenuManager::gomokuPreparation.open();
        }
    );
}

void GomokuMenu::onEnable() {
    startGame();
    Position pos {};
    int radius = 5;
    
    flushmessage();
    while (true) {
        // 消息处理
        ExMessage message = getmessage();
        switch (message.message) {
            // 鼠标左键弹起
            case WM_LBUTTONUP:
                clickButton(message.x, message.y);
                
                if (board.getOrderByPosition(pos, message.x, message.y)) {
                    std::printf("(%d, %d)\n", pos.x, pos.y);
                }
                break;
                
            // 鼠标移动
            case WM_MOUSEMOVE:
                if (isRunning()) {
                    BeginBatchDraw();

                    if (board.getCenterPositionByPosition(pos, message.x, message.y)) {
                        setcolor(GREEN);
                        rectangle(pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius);
                    }

                    FlushBatchDraw();
                }
                break;
        }
    }
}

void GomokuMenu::startGame() {
    setRunning(true);
    
    
}

void GomokuMenu::runGame() {

}

void GomokuMenu::endGame() {
    setRunning(false);
}
