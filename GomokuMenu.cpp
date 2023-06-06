#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-auto"
#include "GomokuMenu.h"
#include "MenuManager.h"
#include "RoundRectangleButton.h"
#include "DisplayButton.h"
#include <cstdio>
#include <thread>

GomokuMenu::GomokuMenu()
            : board(nullptr), timerArea(RECT {}),
              sidebarBaseX(0), sidebarCenterX(0),
              buttonRetract(nullptr), buttonForbidden(nullptr),
              imageBackground(IMAGE(MainMenu::WIDTH, MainMenu::HEIGHT)) {
    loadimage(&imageBackground, "../resources/gomoku_background.jpg", MainMenu::WIDTH, MainMenu::HEIGHT);
}

void GomokuMenu::onOpenInit() {
    // 析构之前的棋盘对象
    delete board;

    // 构造新的棋盘对象
    GomokuOptions &options = MenuManager::gomokuPreparation.getOptions();
    board = new GomokuChessBoard(10, 10, 700, 700, options);
    
    sidebarBaseX = board->getStartX() + board->getTotalWidth() + 20;
    sidebarCenterX = (MainMenu::WIDTH - 20 + sidebarBaseX) / 2;
    
    timerArea = {
        sidebarBaseX,
        board->getStartY(),
        sidebarBaseX + (sidebarCenterX - sidebarBaseX) * 2,
        board->getStartY() + 30
    };
}

void GomokuMenu::onInit() {
    // 绘制背景
    putimage(0, 0, &imageBackground);

    // 绘制棋盘
    board->draw();

    // 绘制计时器
    if (isRunning()) {
        drawTime(getTimer().getTm(), &timerArea);
    } else {
        drawTime(getTimer().getLastTm(), &timerArea);
    }
    
    // 绘制当前回合玩家
    if (isRunning()) {
        board->getRoundPlayer()->getPiece()->draw((timerArea.left + timerArea.right) / 2, timerArea.bottom + 50, 20);
    }
}

void GomokuMenu::initButtons() {
    addButton(
        new RoundRectangleButton("gomoku_preparation", MainMenu::WIDTH, MainMenu::HEIGHT / 2, 100, 50),
        [](Menu &menu, Button &button, int x, int y) {
            auto &gomokuMenu = dynamic_cast<GomokuMenu &>(menu);
            gomokuMenu.setRunning(false);
            
            MenuManager::gomokuPreparation.open();
        }
    );
    
    int radius = 10;
    RECT squareRect = {radius * 2, -radius * 6, radius * 14, radius * 6};
    int squareRectLength = squareRect.right - squareRect.left;

    // 悔棋
    IMAGE *imageRetract = new IMAGE(squareRectLength, squareRectLength);
    loadimage(imageRetract, "../resources/retract.png", squareRectLength, squareRectLength);
    buttonRetract = new CircleSelectionButton("retract", sidebarBaseX + 10, MainMenu::HEIGHT / 4, radius, squareRect, imageRetract);
    addButton(
            buttonRetract,
            [](Menu &menu, Button &button, int x, int y) {
                auto &circleButton = dynamic_cast<CircleSelectionButton &>(button);
                auto &gomokuMenu = dynamic_cast<GomokuMenu &>(menu);
                
                gomokuMenu.board->retract();
                circleButton.setSelected(true);
                
                BeginBatchDraw();
                gomokuMenu.redraw();
                FlushBatchDraw();
            }
    );
    
    // 禁止落子
    buttonForbidden = new RoundRectangleButton("forbidden", 0,0, board->getImageForbidden().getwidth(), board->getImageForbidden().getheight(), &board->getImageForbidden());
    buttonForbidden->setVisible(false);
    buttonForbidden->setVisibleCount(1);
    addButton(
            buttonForbidden,
            [](Menu &menu, Button &button, int x, int y) {
                auto &gomokuMenu = dynamic_cast<GomokuMenu &>(menu);
                
                button.setVisible(false);
                BeginBatchDraw();
                gomokuMenu.redraw();
                FlushBatchDraw();
            }
    );
    
    // 按键提示
    addButton(new DisplayKeyButton(sidebarBaseX + 10, MainMenu::HEIGHT / 2));
}

void GomokuMenu::onEnable() {
    startGame();
    
    Position pos {}, order {};
    Player *player = nullptr;
    User *user = nullptr;
    
    // 计时器线程（每秒更新一次计时器）
    std::thread timerThread([this]() {
        while (isRunning()) {
            buttonForbidden->visibleCountDown();
            
            BeginBatchDraw();
            drawTime(getTimer().getTm(), &timerArea);
            FlushBatchDraw();
            
            Sleep(1000);
        }
    });
    timerThread.detach();
    
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
    getTimer().reset();
    
    // 初始化棋盘
    GomokuOptions &options = MenuManager::gomokuPreparation.getOptions();
    board->init(options);
    
}

void GomokuMenu::runGame(int x, int y) {
    // 尝试落子
    if (!board->placePiece(x, y)) {
        Position pos {};
        board->getCenterPositionByOrder(pos, x, y);
        
        // 显示禁止落子按钮
        buttonForbidden->setX(pos.x);
        buttonForbidden->setY(pos.y);
        buttonForbidden->setVisible(true);
        return;
    }
    
    // 记录落子
    board->record(x, y);
    buttonRetract->setSelected(false);
    
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
    
    onInit();
    
    drawButtons();
}

void GomokuMenu::drawTime(tm *time, RECT *rect) {
    // 保证线程安全
    const std::lock_guard<std::mutex> lock(mutexDrawTime);
    
    clearrectangle(rect->left, rect->top, rect->right, rect->bottom);
    setfillcolor(WHITE);
    solidrectangle(rect->left, rect->top, rect->right, rect->bottom);
    
    settextstyle(30, 15, _T("Consolas"));
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);

    char textTime[15];
    strftime(textTime, sizeof(textTime), "%H:%M:%S", time);
    drawtext(textTime, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

GomokuMenu::~GomokuMenu() {
    delete board;
}

#pragma clang diagnostic pop