#ifndef SUNNYCHESS_GOMOKUMENU_H
#define SUNNYCHESS_GOMOKUMENU_H

#include "Menu.h"
#include "ChessBoard.h"


class GomokuMenu : public Menu {
private:
    ChessBoard board;
    
public:
    GomokuMenu();

    void onInit() override;
    void onEnable() override;

};


#endif //SUNNYCHESS_GOMOKUMENU_H
