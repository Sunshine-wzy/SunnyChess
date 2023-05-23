#include "GomokuPreparationMenu.h"
#include "MenuManager.h"
#include "RoundRectangleButton.h"
#include "CircleSelectionButton.h"


GomokuPreparationMenu::GomokuPreparationMenu() = default;

void GomokuPreparationMenu::onInit() {
    IMAGE imageChessTypeSelection;

    loadimage(&imageChessTypeSelection, "../resources/orderselection.png", 640, 800);   //画三个选项的图片

    putimage(80, 2, &imageChessTypeSelection);
}

void GomokuPreparationMenu::initButtons() {
    options = GomokuOptions();
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
    
    int chessTypeSelectionBaseX = MainMenu::WIDTH / 5;
    int chessTypeSelectionBaseY = MainMenu::HEIGHT / 2;
    auto chessTypeSelectionButtonRandom = new CircleSelectionButton("random", chessTypeSelectionBaseX, chessTypeSelectionBaseY, 120);
    auto chessTypeSelectionButtonBlack = new CircleSelectionButton("black", chessTypeSelectionBaseX * 2, chessTypeSelectionBaseY, 120);
    auto chessTypeSelectionButtonWhite = new CircleSelectionButton("white", chessTypeSelectionBaseX * 3, chessTypeSelectionBaseY, 120);
    
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
