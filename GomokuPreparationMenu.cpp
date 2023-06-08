#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-auto"
#include "GomokuPreparationMenu.h"
#include "MenuManager.h"
#include "RoundRectangleButton.h"


GomokuPreparationMenu::GomokuPreparationMenu()
        : options(GomokuOptions()),
          modeSelectionGroup(SelectionButtonGroup()), numberSelectionGroup(SelectionButtonGroup()),
          sizeSelectionGroup(SelectionButtonGroup()), chessTypeSelectionGroup(SelectionButtonGroup()),
          radius(10), incrementX(MainMenu::WIDTH / 5), incrementY(MainMenu::HEIGHT / 6),
          relativeRect({radius * 2, -radius * 4, radius * 16, radius * 4}),
          smallRelativeRect({radius * 2, -radius * 4, radius * 13, radius * 4}),
          squareRect({radius * 2, -radius * 6, radius * 14, radius * 6}),
          rectWidth(relativeRect.right - relativeRect.left), rectHeight(relativeRect.bottom - relativeRect.top),
          smallRectWidth(smallRelativeRect.right - smallRelativeRect.left), smallRectHeight(smallRelativeRect.bottom - smallRelativeRect.top),
          squareRectWidth(squareRect.right - squareRect.left), squareRectHeight(squareRect.bottom - squareRect.top),
          promptWidth(rectWidth), promptHeight(rectHeight),
          baseX(MainMenu::WIDTH / 30), baseY(MainMenu::HEIGHT / 6),
          imageBackground(IMAGE(MainMenu::WIDTH, MainMenu::HEIGHT)) {
    loadimage(&imageBackground, "../resources/gomoku_preparation_background.png", MainMenu::WIDTH, MainMenu::HEIGHT);
    
    loadimage(&imageModeSelectionPrompt, "../resources/mode_selection_prompt.png", promptWidth, promptHeight);
    loadimage(&imageNumberSelectionPrompt, "../resources/number_selection_prompt.png", promptWidth, promptHeight);
    loadimage(&imageChessTypeSelectionPrompt, "../resources/chess_type_selection_prompt.png", promptWidth, promptHeight);
    loadimage(&imageSizeSelectionPrompt, "../resources/size_selection_prompt.png", promptWidth, promptHeight);
}

void GomokuPreparationMenu::onInit() {
    putimage(0, 0, &imageBackground);
    
    putimage(baseX, baseY, &imageModeSelectionPrompt);
    putimage(baseX, baseY + incrementY, &imageNumberSelectionPrompt);
    putimage(baseX, (int) (baseY + incrementY * 2.15), &imageChessTypeSelectionPrompt);
    putimage(baseX, (int) (baseY + incrementY * 3.3), &imageSizeSelectionPrompt);
    
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

    IMAGE *modeSelectionImageFriend = new IMAGE(rectWidth, rectHeight);
    loadimage(modeSelectionImageFriend, "../resources/mode_selection_friend.png", rectWidth, rectHeight);

    IMAGE *modeSelectionImageBot = new IMAGE(rectWidth, rectHeight);
    loadimage(modeSelectionImageBot, "../resources/mode_selection_bot.png", rectWidth, rectHeight);
    
    // 模式选择按钮
    int modeSelectionBaseX = baseX + promptWidth + 20;
    int modeSelectionBaseY = baseY + promptHeight / 2;
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
        IMAGE *imageNumber = new IMAGE(smallRectWidth, smallRectHeight);
        loadimage(imageNumber, (std::string("../resources/number_selection_") + std::to_string(i + 2) + ".png").c_str(), smallRectWidth, smallRectHeight);
        numberSelectionButtons[i] = new CircleSelectionButton(std::string("number") + std::to_string(i + 2), numberSelectionBaseX + radius * 16 * i, numberSelectionBaseY, radius, smallRelativeRect, imageNumber, std::to_string(i + 2));
        numberSelectionGroup.addButton(numberSelectionButtons[i]);
    }
    addNumberSelectionButton<4>(numberSelectionButtons);
    
    // player1 执子类型选择按钮
    IMAGE *chessTypeSelectionImageRandom = new IMAGE(squareRectWidth, squareRectHeight);
    loadimage(chessTypeSelectionImageRandom, "../resources/chess_type_selection_random.png", squareRectWidth, squareRectHeight);
    IMAGE *chessTypeSelectionImageBlack = new IMAGE(squareRectWidth, squareRectHeight);
    loadimage(chessTypeSelectionImageBlack, "../resources/chess_type_selection_black.png", squareRectWidth, squareRectHeight);
    IMAGE *chessTypeSelectionImageWhite = new IMAGE(squareRectWidth, squareRectHeight);
    loadimage(chessTypeSelectionImageWhite, "../resources/chess_type_selection_white.png", squareRectWidth, squareRectHeight);

    int chessTypeSelectionBaseX = modeSelectionBaseX;
    int chessTypeSelectionBaseY = (int) (modeSelectionBaseY + incrementY * 2.15);
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
    IMAGE *sizeSelectionImage13 = new IMAGE(smallRectWidth, smallRectHeight);
    loadimage(sizeSelectionImage13, "../resources/size_selection_13.png", smallRectWidth, smallRectHeight);
    IMAGE *sizeSelectionImage15 = new IMAGE(smallRectWidth, smallRectHeight);
    loadimage(sizeSelectionImage15, "../resources/size_selection_15.png", smallRectWidth, smallRectHeight);
    IMAGE *sizeSelectionImage17 = new IMAGE(smallRectWidth, smallRectHeight);
    loadimage(sizeSelectionImage17, "../resources/size_selection_17.png", smallRectWidth, smallRectHeight);
    IMAGE *sizeSelectionImage19 = new IMAGE(smallRectWidth, smallRectHeight);
    loadimage(sizeSelectionImage19, "../resources/size_selection_19.png", smallRectWidth, smallRectHeight);
    IMAGE *sizeSelectionImage21 = new IMAGE(smallRectWidth, smallRectHeight);
    loadimage(sizeSelectionImage21, "../resources/size_selection_21.png", smallRectWidth, smallRectHeight);

    int sizeSelectionBaseX = modeSelectionBaseX;
    int sizeSelectionBaseY = (int) (modeSelectionBaseY + incrementY * 3.3);
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
    
    // 开始游戏
    addButton(
            new RoundRectangleButton("gomoku", MainMenu::WIDTH / 2, (int) (sizeSelectionBaseY + incrementY * 0.8)),
            [](Menu &menu, Button &button, int x, int y) {
                MenuManager::gomoku.open();
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


#pragma clang diagnostic pop