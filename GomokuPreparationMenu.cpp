#include "GomokuPreparationMenu.h"
#include "MenuManager.h"
#include "RoundRectangleButton.h"
#include "CircleSelectionButton.h"


GomokuPreparationMenu::GomokuPreparationMenu() = default;

void GomokuPreparationMenu::onInit() {

}

void GomokuPreparationMenu::initButtons() {
    chessTypeSelectionGroup.clear();
    
    auto circleButton1 = new CircleSelectionButton("black", MainMenu::WIDTH / 2 - 30, MainMenu::HEIGHT / 2, 10);
    auto circleButton2 = new CircleSelectionButton("white", MainMenu::WIDTH / 2, MainMenu::HEIGHT / 2, 10);
    auto circleButton3 = new CircleSelectionButton("random", MainMenu::WIDTH / 2 + 30, MainMenu::HEIGHT / 2, 10);
    
    chessTypeSelectionGroup
            .addButton(circleButton1)
            .addButton(circleButton2)
            .addButton(circleButton3);

    chessTypeSelectionGroup.select(circleButton1);
    
    addButton(
            circleButton1,
            [](Menu &menu, Button &button, int x, int y) {
                auto &circleButton = dynamic_cast<CircleSelectionButton &>(button);
                auto &gomokuMenu = dynamic_cast<GomokuPreparationMenu &>(menu);
                gomokuMenu.chessTypeSelectionGroup.select(&circleButton);
                menu.reopen();
            }
    );

    addButton(
            circleButton2,
            [](Menu &menu, Button &button, int x, int y) {
                auto &circleButton = dynamic_cast<CircleSelectionButton &>(button);
                auto &gomokuMenu = dynamic_cast<GomokuPreparationMenu &>(menu);
                gomokuMenu.chessTypeSelectionGroup.select(&circleButton);
                menu.reopen();
            }
    );

    addButton(
            circleButton3,
            [](Menu &menu, Button &button, int x, int y) {
                auto &circleButton = dynamic_cast<CircleSelectionButton &>(button);
                auto &gomokuMenu = dynamic_cast<GomokuPreparationMenu &>(menu);
                gomokuMenu.chessTypeSelectionGroup.select(&circleButton);
                menu.reopen();
            }
    );


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

//const SelectionButtonGroup &GomokuPreparationMenu::getChessTypeSelectionGroup() const {
//    return chessTypeSelectionGroup;
//}
