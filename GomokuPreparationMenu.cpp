#include "GomokuPreparationMenu.h"
#include "MenuManager.h"
#include "RoundRectangleButton.h"


GomokuPreparationMenu::GomokuPreparationMenu() = default;

void GomokuPreparationMenu::onInit() {
    if (modeSelectionGroup.isKeySelected("friend")) {
        numberSelectionGroup.setVisible(true);
    } else {
        numberSelectionGroup.setVisible(false);
    }
    
    if (modeSelectionGroup.isKeySelected("bot") || numberSelectionGroup.isKeySelected("number2")) {
        chessTypeSelectionGroup.setVisible(true);
    } else {
        chessTypeSelectionGroup.setVisible(false);
    }
}

void GomokuPreparationMenu::initButtons() {
    options = GomokuOptions();
    options.size = 15;
    
    modeSelectionGroup.clear();
    numberSelectionGroup.clear();
    sizeSelectionGroup.clear();
    chessTypeSelectionGroup.clear();

    addButton(
            new RoundRectangleButton("gomoku", MainMenu::WIDTH, MainMenu::HEIGHT * 1 / 3, 100, 50),
            [](Menu &menu, Button &button, int x, int y) {
                MenuManager::gomoku.open();
            }
    );
    addButton(
            new RoundRectangleButton("main", MainMenu::WIDTH, MainMenu::HEIGHT * 2 / 3, 100, 50),
            [](Menu &menu, Button &button, int x, int y) {
                MenuManager::main.open();
            }
    );

    int radius = 10;
    RECT relativeRect = {radius * 2, -radius * 4, radius * 16, radius * 4};
    RECT smallRelativeRect = {radius * 2, -radius * 4, radius * 13, radius * 4};
    RECT squareRect = {radius * 2, -radius * 6, radius * 14, radius * 6};
    
    int rectWidth = relativeRect.right - relativeRect.left;
    int rectHeight = relativeRect.bottom - relativeRect.top;
    int smallRectWidth = smallRelativeRect.right - smallRelativeRect.left;
    int smallRectHeight = smallRelativeRect.bottom - smallRelativeRect.top;
    int squareRectWidth = squareRect.right - squareRect.left;
    int squareRectHeight = squareRect.bottom - squareRect.top;

    IMAGE *modeSelectionImageFriend = new IMAGE(rectWidth, rectHeight);
    loadimage(modeSelectionImageFriend, "../resources/friend.png", rectWidth, rectHeight);

    IMAGE *modeSelectionImageBot = new IMAGE(rectWidth, rectHeight); // NOLINT(modernize-use-auto)
    loadimage(modeSelectionImageBot, "../resources/bot.png", rectWidth, rectHeight);
    
    int incrementX = MainMenu::WIDTH / 5;
    int incrementY = MainMenu::HEIGHT / 6;
    
    // 模式选择按钮
    int modeSelectionBaseX = MainMenu::WIDTH / 8;
    int modeSelectionBaseY = MainMenu::HEIGHT / 5;
    // 好友对局
    auto modeSelectionButtonFriend = new CircleSelectionButton("friend", modeSelectionBaseX, modeSelectionBaseY, radius, relativeRect, modeSelectionImageFriend);
    // 人机对战
    auto modeSelectionButtonBot = new CircleSelectionButton("bot", modeSelectionBaseX + incrementX, modeSelectionBaseY, radius, relativeRect, modeSelectionImageBot);
    modeSelectionGroup
            .addButton(modeSelectionButtonFriend)
            .addButton(modeSelectionButtonBot);
    addButton(
            modeSelectionButtonFriend,
            [](Menu &menu, Button &button, int x, int y) {
                auto &circleButton = dynamic_cast<CircleSelectionButton &>(button);
                auto &gomokuMenu = dynamic_cast<GomokuPreparationMenu &>(menu);

                gomokuMenu.modeSelectionGroup.select(&circleButton);
                gomokuMenu.options.mode = GomokuOptions::Mode::FRIEND;
                menu.reopen();
            }
    );
    addButton(
            modeSelectionButtonBot,
            [](Menu &menu, Button &button, int x, int y) {
                auto &circleButton = dynamic_cast<CircleSelectionButton &>(button);
                auto &gomokuMenu = dynamic_cast<GomokuPreparationMenu &>(menu);

                gomokuMenu.modeSelectionGroup.select(&circleButton);
                gomokuMenu.options.mode = GomokuOptions::Mode::BOT;
                menu.reopen();
            }
    );
    
    // 玩家数量选择按钮
    int numberSelectionBaseX = modeSelectionBaseX;
    int numberSelectionBaseY = modeSelectionBaseY + incrementY;
    CircleSelectionButton *numberSelectionButtons[5];
    for (int i = 0; i < 5; i++) {
        numberSelectionButtons[i] = new CircleSelectionButton(std::string("number") + std::to_string(i + 2), numberSelectionBaseX + radius * 16 * i, numberSelectionBaseY, radius, smallRelativeRect, nullptr, std::to_string(i + 2));
        numberSelectionGroup.addButton(numberSelectionButtons[i]);
    }
    addNumberSelectionButton<4>(numberSelectionButtons);
    
    // player1 执子类型选择按钮
    // TODO: IMAGE
    IMAGE *chessTypeSelectionImageRandom = new IMAGE(squareRectWidth, squareRectHeight);
    loadimage(chessTypeSelectionImageRandom, "../resources/randomchess.png", squareRectWidth, squareRectHeight);
    IMAGE *chessTypeSelectionImageBlack = new IMAGE(squareRectWidth, squareRectHeight);
    loadimage(chessTypeSelectionImageBlack, "../resources/blackchess.png", squareRectWidth, squareRectHeight);
    IMAGE *chessTypeSelectionImageWhite = new IMAGE(squareRectWidth, squareRectHeight);
    loadimage(chessTypeSelectionImageWhite, "../resources/whitechess.png", squareRectWidth, squareRectHeight);

    int chessTypeSelectionBaseX = modeSelectionBaseX;
    int chessTypeSelectionBaseY = modeSelectionBaseY + incrementY * 2.15;
    auto chessTypeSelectionButtonRandom = new CircleSelectionButton("random", chessTypeSelectionBaseX, chessTypeSelectionBaseY, radius, squareRect, chessTypeSelectionImageRandom);
    auto chessTypeSelectionButtonBlack = new CircleSelectionButton("black", chessTypeSelectionBaseX + incrementX, chessTypeSelectionBaseY, radius, squareRect, chessTypeSelectionImageBlack);
    auto chessTypeSelectionButtonWhite = new CircleSelectionButton("white", chessTypeSelectionBaseX + incrementX * 2, chessTypeSelectionBaseY, radius, squareRect, chessTypeSelectionImageWhite);
    chessTypeSelectionGroup
            .addButton(chessTypeSelectionButtonRandom)
            .addButton(chessTypeSelectionButtonBlack)
            .addButton(chessTypeSelectionButtonWhite);
    addButton(
            chessTypeSelectionButtonRandom,
            [](Menu &menu, Button &button, int x, int y) {
                auto &circleButton = dynamic_cast<CircleSelectionButton &>(button);
                auto &gomokuMenu = dynamic_cast<GomokuPreparationMenu &>(menu);
                
                gomokuMenu.chessTypeSelectionGroup.select(&circleButton);
                gomokuMenu.options.type = ChessPiece::none;
                menu.reopen();
            }
    );
    addButton(
            chessTypeSelectionButtonBlack,
            [](Menu &menu, Button &button, int x, int y) {
                auto &circleButton = dynamic_cast<CircleSelectionButton &>(button);
                auto &gomokuMenu = dynamic_cast<GomokuPreparationMenu &>(menu);
                
                gomokuMenu.chessTypeSelectionGroup.select(&circleButton);
                gomokuMenu.options.type = ChessPiece::black;
                menu.reopen();
            }
    );
    addButton(
            chessTypeSelectionButtonWhite,
            [](Menu &menu, Button &button, int x, int y) {
                auto &circleButton = dynamic_cast<CircleSelectionButton &>(button);
                auto &gomokuMenu = dynamic_cast<GomokuPreparationMenu &>(menu);
                
                gomokuMenu.chessTypeSelectionGroup.select(&circleButton);
                gomokuMenu.options.type = ChessPiece::white;
                menu.reopen();
            }
    );

    // 棋盘大小选择按钮
    // TODO: IMAGE
    IMAGE *sizeSelectionImage13 = new IMAGE(rectWidth, rectHeight);
    loadimage(sizeSelectionImage13, "../resources/sizeofchesspan13.png", rectWidth, rectHeight);
    IMAGE *sizeSelectionImage15 = new IMAGE(rectWidth, rectHeight);
    loadimage(sizeSelectionImage15, "../resources/sizeofchesspan15.png", rectWidth, rectHeight);
    IMAGE *sizeSelectionImage17 = new IMAGE(rectWidth, rectHeight);
    loadimage(sizeSelectionImage17, "../resources/sizeofchesspan17.png", rectWidth, rectHeight);
    IMAGE *sizeSelectionImage19 = new IMAGE(rectWidth, rectHeight);
    loadimage(sizeSelectionImage19, "../resources/sizeofchesspan19.png", rectWidth, rectHeight);
    IMAGE *sizeSelectionImage21 = new IMAGE(rectWidth, rectHeight);
    loadimage(sizeSelectionImage21, "../resources/sizeofchesspan21.png", rectWidth, rectHeight);

    int sizeSelectionBaseX = modeSelectionBaseX;
    int sizeSelectionBaseY = modeSelectionBaseY + incrementY * 3.3;
    auto sizeSelectionButton13 = new CircleSelectionButton("size13", sizeSelectionBaseX, sizeSelectionBaseY, radius, smallRelativeRect, sizeSelectionImage13);
    auto sizeSelectionButton15 = new CircleSelectionButton("size15", sizeSelectionBaseX + radius * 16, sizeSelectionBaseY, radius, smallRelativeRect, sizeSelectionImage15);
    auto sizeSelectionButton17 = new CircleSelectionButton("size17", sizeSelectionBaseX + radius * 16 * 2, sizeSelectionBaseY, radius, smallRelativeRect, sizeSelectionImage17);
    auto sizeSelectionButton19 = new CircleSelectionButton("size19", sizeSelectionBaseX + radius * 16 * 3, sizeSelectionBaseY, radius, smallRelativeRect, sizeSelectionImage19);
    auto sizeSelectionButton21 = new CircleSelectionButton("size21", sizeSelectionBaseX + radius * 16 * 4, sizeSelectionBaseY, radius, smallRelativeRect, sizeSelectionImage21);
    sizeSelectionGroup
            .addButton(sizeSelectionButton13)
            .addButton(sizeSelectionButton15)
            .addButton(sizeSelectionButton17)
            .addButton(sizeSelectionButton19)
            .addButton(sizeSelectionButton21)
            .select(sizeSelectionButton15);
    addButton(
            sizeSelectionButton13,
            [](Menu &menu, Button &button, int x, int y) {
                auto &circleButton = dynamic_cast<CircleSelectionButton &>(button);
                auto &gomokuMenu = dynamic_cast<GomokuPreparationMenu &>(menu);

                gomokuMenu.sizeSelectionGroup.select(&circleButton);
                gomokuMenu.options.size = 13;
                menu.reopen();
            }
    );
    addButton(
            sizeSelectionButton15,
            [](Menu &menu, Button &button, int x, int y) {
                auto &circleButton = dynamic_cast<CircleSelectionButton &>(button);
                auto &gomokuMenu = dynamic_cast<GomokuPreparationMenu &>(menu);

                gomokuMenu.sizeSelectionGroup.select(&circleButton);
                gomokuMenu.options.size = 15;
                menu.reopen();
            }
    );
    addButton(
            sizeSelectionButton17,
            [](Menu &menu, Button &button, int x, int y) {
                auto &circleButton = dynamic_cast<CircleSelectionButton &>(button);
                auto &gomokuMenu = dynamic_cast<GomokuPreparationMenu &>(menu);

                gomokuMenu.sizeSelectionGroup.select(&circleButton);
                gomokuMenu.options.size = 17;
                menu.reopen();
            }
    );
    addButton(
            sizeSelectionButton19,
            [](Menu &menu, Button &button, int x, int y) {
                auto &circleButton = dynamic_cast<CircleSelectionButton &>(button);
                auto &gomokuMenu = dynamic_cast<GomokuPreparationMenu &>(menu);

                gomokuMenu.sizeSelectionGroup.select(&circleButton);
                gomokuMenu.options.size = 19;
                menu.reopen();
            }
    );
    addButton(
            sizeSelectionButton21,
            [](Menu &menu, Button &button, int x, int y) {
                auto &circleButton = dynamic_cast<CircleSelectionButton &>(button);
                auto &gomokuMenu = dynamic_cast<GomokuPreparationMenu &>(menu);

                gomokuMenu.sizeSelectionGroup.select(&circleButton);
                gomokuMenu.options.size = 21;
                menu.reopen();
            }
    );
}

void GomokuPreparationMenu::onEnable() {
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

GomokuOptions &GomokuPreparationMenu::getOptions() {
    return options;
}

template <>
void GomokuPreparationMenu::addNumberSelectionButton<-1>(CircleSelectionButton *buttons[]) {}

