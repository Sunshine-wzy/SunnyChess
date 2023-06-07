#ifndef SUNNYCHESS_GOMOKUMENU_H
#define SUNNYCHESS_GOMOKUMENU_H

#include "Menu.h"
#include "GomokuChessBoard.h"
#include "Game.h"
#include "CircleSelectionButton.h"
#include "RoundRectangleButton.h"
#include "DisplayButton.h"
#include <mutex>


class GomokuMenu : public Menu, public Game {
private:
    GomokuChessBoard *board;
    RECT timerArea;
    int sidebarBaseX;
    int sidebarCenterX;
    
    CircleSelectionButton *buttonRetract;
    RoundRectangleButton *buttonForbidden;
    DisplayKeyButton *buttonDisplayKey;

    IMAGE imageBackground;
    IMAGE imageVictory;
    
    std::mutex mutexRedraw;
    std::mutex mutexDrawTime;

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

    template <class Callable>
    void redraw(Callable &&callable, bool isRedraw = true);
    
    void redraw();
    
    void drawTime(tm *time, RECT *rect);
    
    void runBot(Bot &bot);
    
    void calculateScore(Bot &bot);
    
    Position botThink(Bot &bot);

};


template <class Callable>
void GomokuMenu::redraw(Callable &&callable, bool isRedraw) {
    const std::lock_guard<std::mutex> lock(mutexRedraw);

    BeginBatchDraw();

    if (isRedraw) {
        cleardevice();
        onInit();
        drawButtons();
    }
    
    callable();

    FlushBatchDraw();
}


#endif //SUNNYCHESS_GOMOKUMENU_H
