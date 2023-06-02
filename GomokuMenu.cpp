#include "GomokuMenu.h"
#include "MenuManager.h"
#include "RoundRectangleButton.h"
#include <cstdio>

GomokuMenu::GomokuMenu() : board(nullptr) {}

void GomokuMenu::onOpenInit() {
    // 析构之前的棋盘对象
    delete board;

    // 构造新的棋盘对象
    GomokuOptions &options = MenuManager::gomokuPreparation.getOptions();
    board = new GomokuChessBoard(10, 10, 700, 700, options);
}

void GomokuMenu::onInit() {
    board->draw();
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
    
    flushmessage();
    while (true) {
        // 消息处理
        ExMessage message = getmessage();
        if (isRunning()) {
            User *user = dynamic_cast<User *>(board->getRoundPlayer());
            if (user != nullptr) {
                user->onExMessage(message);
            }
        }
        
        switch (message.message) {
            // 鼠标左键弹起
            case WM_LBUTTONUP:
                // 点击按钮
                clickButton(message.x, message.y);
                
                if (isRunning()) {
                    if (board->getOrderByPosition(pos, message.x, message.y)) {
                        std::printf("(%d, %d)\n", pos.x, pos.y);

                        // 执行游戏逻辑
                        runGame(pos.x, pos.y);

                        BeginBatchDraw();
                        redraw();
                        FlushBatchDraw();
                    }
                }
                break;
        }
    }
}

void GomokuMenu::startGame() {
    setRunning(true);
    
    // 初始化棋盘
    GomokuOptions &options = MenuManager::gomokuPreparation.getOptions();
    board->init(options);
    
}

void GomokuMenu::runGame(int x, int y) {
    // 尝试落子
    if (!board->placePiece(x, y)) return;
    
    // 胜利判定
    if (board->judge(x, y)) {
        // 游戏结束
        endGame();

        return;
    }
    
    // 回合更替
    board->turnRound();
}

void GomokuMenu::endGame() {
    setRunning(false);
}

void GomokuMenu::redraw() {
    cleardevice();
    
    board->draw();
    
    drawButtons();
}
