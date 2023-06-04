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
    
    Position pos {}, order {};
    Player *player = nullptr;
    User *user = nullptr;
    
    flushmessage();
    while (true) {
        // 消息处理
        ExMessage message = getmessage();
        if (isRunning()) {
            player = board->getRoundPlayer();
            user = dynamic_cast<User *>(player);
        }
        
        switch (message.message) {
            // 鼠标左键弹起
            case WM_LBUTTONUP:
                // 点击按钮
                clickButton(message.x, message.y);
                
                if (isRunning()) {
                    if (player && board->getOrderByPosition(pos, message.x, message.y)) {
                        std::printf("(%d, %d)\n", pos.x, pos.y);

                        // 执行游戏逻辑
                        runGame(pos.x, pos.y);

                        BeginBatchDraw();
                        redraw();

                        // 在落子位置画出新一轮玩家的选择框
                        if (board->getCenterPositionByOrder(pos, player->selectionBoxOrder.x, player->selectionBoxOrder.y)) {
                            board->getRoundPlayer()->onSelectionBoxDraw(pos, player->selectionBoxOrder);
                        }
                        
                        FlushBatchDraw();
                    }
                }
                break;

            // 鼠标移动
            case WM_MOUSEMOVE:
                if (isRunning()) {
                    if (player && board->getCenterPositionByPosition(pos, message.x, message.y)) {
                        BeginBatchDraw();
                        redraw();

                        // 画出选择框
                        if (board->getOrderByPosition(order, message.x, message.y)) {
                            player->onSelectionBoxDraw(pos, order);
                        }

                        FlushBatchDraw();
                    }
                }
                break;

            // 按键按下
            case WM_KEYDOWN:
                if (isRunning()) {
                    if (user) {
                        int x = 0, y = 0;

                        if (message.vkcode == user->getKeySettings().up) {
                            x = user->selectionBoxOrder.x;
                            y = user->selectionBoxOrder.y - 1;
                        } else if (message.vkcode == user->getKeySettings().down) {
                            x = user->selectionBoxOrder.x;
                            y = user->selectionBoxOrder.y + 1;
                        } else if (message.vkcode == user->getKeySettings().left) {
                            x = user->selectionBoxOrder.x - 1;
                            y = user->selectionBoxOrder.y;
                        } else if (message.vkcode == user->getKeySettings().right) {
                            x = user->selectionBoxOrder.x + 1;
                            y = user->selectionBoxOrder.y;
                        } else if (message.vkcode == user->getKeySettings().drop) {
                            // 落子
                            std::printf("(%d, %d)\n", user->selectionBoxOrder.x, user->selectionBoxOrder.y);

                            // 执行游戏逻辑
                            runGame(user->selectionBoxOrder.x, user->selectionBoxOrder.y);

                            BeginBatchDraw();
                            redraw();
                            
                            // 在落子位置画出新一轮玩家的选择框
                            if (board->getCenterPositionByOrder(pos, user->selectionBoxOrder.x, user->selectionBoxOrder.y)) {
                                board->getRoundPlayer()->onSelectionBoxDraw(pos, user->selectionBoxOrder);
                            }
                            
                            FlushBatchDraw();
                            break;
                        }

                        if (board->isOrderInBoard(x, y) && board->getCenterPositionByOrder(pos, x, y)) {
                            BeginBatchDraw();
                            redraw();
                            
                            order.x = x;
                            order.y = y;
                            user->onSelectionBoxDraw(pos, order);
                            
                            FlushBatchDraw();
                        }
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
    if (!board->placePiece(x, y)) {
        Position pos {};
        board->getCenterPositionByOrder(pos, x, y);
        // 绘制禁止落子图标
        putimage(pos.x, pos.y, &board->getImageForbidden(), SRCPAINT);
        return;
    }
    
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
