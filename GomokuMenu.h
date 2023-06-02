#ifndef SUNNYCHESS_GOMOKUMENU_H
#define SUNNYCHESS_GOMOKUMENU_H

#include "Menu.h"
#include "GomokuChessBoard.h"
#include "Game.h"


class GomokuMenu : public Menu, public Game {
private:
    GomokuChessBoard *board;

public:
    GomokuMenu();

    void onOpenInit() override;
    
    void onInit() override;

    void onEnable() override;

    void startGame() override;

    void runGame(int x, int y) override;

    void endGame() override;

    void initButtons() override;
    
    void redraw() override;

};


#endif //SUNNYCHESS_GOMOKUMENU_H
