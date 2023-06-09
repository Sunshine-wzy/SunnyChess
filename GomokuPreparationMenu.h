#ifndef SUNNYCHESS_GOMOKUPREPARATIONMENU_H
#define SUNNYCHESS_GOMOKUPREPARATIONMENU_H

#include "GomokuMenu.h"
#include "ChessOptions.h"
#include "SelectionButtonGroup.h"
#include "CircleSelectionButton.h"


class GomokuPreparationMenu : public Menu {
private:
    GomokuOptions options;
    
    SelectionButtonGroup modeSelectionGroup;
    SelectionButtonGroup numberSelectionGroup;
    SelectionButtonGroup sizeSelectionGroup;
    SelectionButtonGroup chessTypeSelectionGroup;
    
    int radius;
    int incrementX;
    int incrementY;
    
    RECT relativeRect;
    RECT smallRelativeRect;
    RECT squareRect;
    
    int rectWidth;
    int rectHeight;
    int smallRectWidth;
    int smallRectHeight;
    int squareRectWidth;
    int squareRectHeight;
    
    int promptWidth;
    int promptHeight;
    
    int baseX;
    int baseY;

    IMAGE imageBackground;
    IMAGE imageTitle;
    IMAGE imageModeSelectionPrompt;
    IMAGE imageNumberSelectionPrompt;
    IMAGE imageChessTypeSelectionPrompt;
    IMAGE imageSizeSelectionPrompt;
    
    
    template <int Number>
    void addNumberSelectionButton(CircleSelectionButton *buttons[]);
    
public:
    GomokuPreparationMenu();

    void onInit() override;

    void onEnable() override;

    void initButtons() override;

    GomokuOptions &getOptions();

};


template <int Number>
void GomokuPreparationMenu::addNumberSelectionButton(CircleSelectionButton *buttons[]) {
    addButton(
            buttons[Number],
            [](Menu &menu, Button &button, int x, int y) {
                auto &circleButton = dynamic_cast<CircleSelectionButton &>(button);
                auto &gomokuMenu = dynamic_cast<GomokuPreparationMenu &>(menu);

                gomokuMenu.numberSelectionGroup.select(&circleButton);
                gomokuMenu.options.number = Number + 2;
                menu.reopen();
            }
    );

    addNumberSelectionButton<Number - 1>(buttons);
}


#endif //SUNNYCHESS_GOMOKUPREPARATIONMENU_H
