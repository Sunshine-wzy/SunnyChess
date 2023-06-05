#ifndef SUNNYCHESS_GOMOKUMENU_H
#define SUNNYCHESS_GOMOKUMENU_H

#include "Menu.h"
#include "GomokuChessBoard.h"
#include "Game.h"
#include "CircleSelectionButton.h"
#include "RoundRectangleButton.h"


class GomokuMenu : public Menu, public Game {
private:
    GomokuChessBoard *board;
    RECT timerArea;
    int sidebarBaseX;
    int sidebarCenterX;
    
    CircleSelectionButton *buttonRetract;
    RoundRectangleButton *buttonForbidden;

    IMAGE imageBackground;

public:
    GomokuMenu();

    ~GomokuMenu() override;

    void onOpenInit() override;
    
    void onInit() override;

    void onEnable() override;

    void startGame() override;

    void runGame(int x, int y) override;

    void endGame() override;

    void initButtons() override;
    
    void redraw();
    
    
    static void drawTime(tm *time, RECT *rect);

};


#endif //SUNNYCHESS_GOMOKUMENU_H
