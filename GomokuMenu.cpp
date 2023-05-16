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
    int selectBoxHalfWidth = (int) (board.getSlotWidth() / 2);
    int selectBoxHalfHeight = (int) (board.getSlotHeight() / 2);
    
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
                    
                    board.placePiece(ChessPiece::white, pos.x, pos.y);
                    
                    BeginBatchDraw();
                    redraw();
                    FlushBatchDraw();
                }
                break;
                
            // 鼠标移动
            case WM_MOUSEMOVE:
                if (isRunning()) {
                    if (board.getCenterPositionByPosition(pos, message.x, message.y)) {
                        BeginBatchDraw();
                        redraw();
                        
                        setcolor(0x9FC57);
                        setlinestyle(PS_DASH | PS_ENDCAP_SQUARE);
                        rectangle(pos.x - selectBoxHalfWidth, pos.y - selectBoxHalfHeight, pos.x + selectBoxHalfWidth, pos.y + selectBoxHalfHeight);
                        FlushBatchDraw();
                    }
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

void GomokuMenu::redraw() {
    cleardevice();
    
    board.draw();
    
    drawButtons();
}
