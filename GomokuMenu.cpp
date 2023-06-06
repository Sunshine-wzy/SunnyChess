#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-auto"
#include "GomokuMenu.h"
#include "MenuManager.h"
#include "RoundRectangleButton.h"
#include <cstdio>
#include <thread>

GomokuMenu::GomokuMenu()
            : board(nullptr), timerArea(RECT {}),
              sidebarBaseX(0), sidebarCenterX(0),
              buttonRetract(nullptr), buttonForbidden(nullptr), buttonDisplayKey(nullptr),
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
    buttonRetract = new CircleSelectionButton("retract", sidebarBaseX + 10, MainMenu::HEIGHT / 2, radius, squareRect, imageRetract);
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
    buttonDisplayKey = new DisplayKeyButton(sidebarBaseX + 10, timerArea.bottom + 100);
    addButton(buttonDisplayKey);
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
                    if (user && board->getOrderByPosition(pos, message.x, message.y)) {
                        // 执行游戏逻辑
                        runGame(pos.x, pos.y);

                        Bot *bot = dynamic_cast<Bot *>(board->getRoundPlayer());
                        if (bot) {
                            runBot(*bot);
                        }
                    }
                }
                break;

            // 鼠标移动
            case WM_MOUSEMOVE:
                if (isRunning()) {
                    if (user && board->getCenterPositionByPosition(pos, message.x, message.y)) {
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
                            // 执行游戏逻辑
                            runGame(user->selectionBoxOrder.x, user->selectionBoxOrder.y);

                            Bot *bot = dynamic_cast<Bot *>(board->getRoundPlayer());
                            if (bot) {
                                runBot(*bot);
                            }
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
    
    // 初始化按键提示
    User *user = dynamic_cast<User *>(board->getRoundPlayer());
    if (user) {
        buttonDisplayKey->setKeySettings(&user->getKeySettings());
    }
    
    // 刷新界面
    BeginBatchDraw();
    redraw();
    FlushBatchDraw();
    
    // 尝试运行bot
    Bot *bot = dynamic_cast<Bot *>(board->getRoundPlayer());
    if (bot) {
        runBot(*bot);
    }
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
    
    Player *lastPlayer = board->getRoundPlayer();
    
    // 回合更替
    board->turnRound();
    
    Player *nowPlayer = board->getRoundPlayer();
    BeginBatchDraw();
    redraw();

    // 在落子位置画出新一轮玩家的选择框
    Position pos {x, y};
    if (board->getCenterPositionByOrder(pos, x, y)) {
        nowPlayer->onSelectionBoxDraw(pos, lastPlayer->selectionBoxOrder);
    }

    FlushBatchDraw();
    
    User *user = dynamic_cast<User *>(nowPlayer);
    if (user) {
        buttonDisplayKey->setKeySettings(&user->getKeySettings());
    } else {
        buttonDisplayKey->setKeySettings(nullptr);
    }
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

void GomokuMenu::runBot(Bot &bot) {
    Position order = botThink(bot);
    runGame(order.x, order.y);
}

void GomokuMenu::calculateScore(Bot &bot) {
    // 评分向量数组清零
    for (auto &vec : bot.scoreMap) {
        for (int &score : vec) {
            score = 0;
        }
    }
    
    // user连续棋子数
    int userNum = 0;
    // bot连续棋子数
    int botNum = 0;
    // 空白位个数
    int noneNum = 0;
    
    ChessPiece *userPiece = bot.getUser().getPiece();
    ChessPiece *botPiece = bot.getPiece();
    int size = board->getSize();
    for (int x = 1; x <= size; x++) {
        for (int y = 1; y <= size; y++) {
            // 对每个点进行计算
            ChessPiece *piece = board->getPiece(x, y);
            if (piece != nullptr && piece != ChessPiece::none) continue;
            
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx == 0 && dy != 1) continue;
                    
                    // 假设user在该位置落子，会构成什么棋型
                    noneNum = 0;
                    userNum = 0;
                    
                    for (int i = 1; i <= 4; i++) {
                        int curX = x + i * dx;
                        int curY = y + i * dy;

                        if (board->isOrderInBoard(curX, curY)) {
                            ChessPiece *curPiece = board->getPiece(curX, curY);
                            if (curPiece == nullptr || curPiece == ChessPiece::none) {
                                noneNum++;
                                break;
                            } else if (curPiece == userPiece) {
                                userNum++;
                            } else break;
                        } else break;
                    }
                    
                    // 反向继续计算
                    for (int i = 1; i <= 4; i++) {
                        int curX = x - i * dx;
                        int curY = y - i * dy;

                        if (board->isOrderInBoard(curX, curY)) {
                            ChessPiece *curPiece = board->getPiece(curX, curY);
                            if (curPiece == nullptr || curPiece == ChessPiece::none) {
                                noneNum++;
                                break;
                            } else if (curPiece == userPiece) {
                                userNum++;
                            } else break;
                        } else break;
                    }
                    
                    if (userNum == 1) {
                        // 连2
                        bot.scoreMap[x][y] += 10;
                    } else if (userNum == 2) {
                        // 连3
                        if (noneNum == 1) {
                            // 死3
                            bot.scoreMap[x][y] += 30;
                        } else if (noneNum == 2) {
                            // 活3
                            bot.scoreMap[x][y] += 40;
                        }
                    } else if (userNum == 3) {
                        // 连4
                        if (noneNum == 1) {
                            // 死4
                            bot.scoreMap[x][y] += 60;
                        } else if (noneNum == 2) {
                            // 活4
                            bot.scoreMap[x][y] += 200;
                        }
                    } else if (userNum == 4) {
                        // 连5
                        bot.scoreMap[x][y] += 20000;
                    }

                    
                    // 假设bot在该位置落子，会构成什么棋型
                    noneNum = 0;
                    botNum = 0;

                    for (int i = 1; i <= 4; i++) {
                        int curX = x + i * dx;
                        int curY = y + i * dy;

                        if (board->isOrderInBoard(curX, curY)) {
                            ChessPiece *curPiece = board->getPiece(curX, curY);
                            if (curPiece == nullptr || curPiece == ChessPiece::none) {
                                noneNum++;
                                break;
                            } else if (curPiece == botPiece) {
                                botNum++;
                            } else break;
                        } else break;
                    }

                    // 反向继续计算
                    for (int i = 1; i <= 4; i++) {
                        int curX = x - i * dx;
                        int curY = y - i * dy;

                        if (board->isOrderInBoard(curX, curY)) {
                            ChessPiece *curPiece = board->getPiece(curX, curY);
                            if (curPiece == nullptr || curPiece == ChessPiece::none) {
                                noneNum++;
                                break;
                            } else if (curPiece == botPiece) {
                                botNum++;
                            } else break;
                        } else break;
                    }

                    if (botNum == 0) {
                        bot.scoreMap[x][y] += 1;
                    } else if (botNum == 1) {
                        // 连2
                        bot.scoreMap[x][y] += 10;
                    } else if (botNum == 2) {
                        // 连3
                        if (noneNum == 1) {
                            // 死3
                            bot.scoreMap[x][y] += 25;
                        } else if (noneNum == 2) {
                            // 活3
                            bot.scoreMap[x][y] += 50;
                        }
                    } else if (botNum == 3) {
                        // 连4
                        if (noneNum == 1) {
                            // 死4
                            bot.scoreMap[x][y] += 55;
                        } else if (noneNum == 2) {
                            // 活4
                            bot.scoreMap[x][y] += 10000;
                        }
                    } else if (botNum == 4) {
                        // 连5
                        bot.scoreMap[x][y] += 30000;
                    }
                }
            }
        }
    }
}

Position GomokuMenu::botThink(Bot &bot) {
    calculateScore(bot);

    int size = board->getSize();
    int maxScore = 0;
    std::vector<Position> maxPoints;

    for (int x = 1; x <= size; x++) {
        for (int y = 1; y <= size; y++) {
            ChessPiece *piece = board->getPiece(x, y);
            if (piece == nullptr || piece == ChessPiece::none) {
                int theScore = bot.scoreMap[x][y];
                
                if (theScore > maxScore) {
                    maxScore = bot.scoreMap[x][y];
                    maxPoints.clear();
                    maxPoints.emplace_back(Position {x, y});
                } else if (bot.scoreMap[x][y] == maxScore) {
                    maxPoints.emplace_back(Position {x, y});
                }
            }
        }
    }

    if (maxPoints.empty()) {
        return {0, 0};
    }
    
    int index = std::rand() % (int) maxPoints.size(); // NOLINT(cert-msc50-cpp)
    return maxPoints[index];
}

#pragma clang diagnostic pop