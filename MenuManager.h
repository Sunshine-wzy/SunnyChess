#ifndef SUNNYCHESS_MENUMANAGER_H
#define SUNNYCHESS_MENUMANAGER_H

#include "MainMenu.h"
#include "GomokuPreparationMenu.h"
#include "GomokuMenu.h"

class MenuManager {
public:
    static MainMenu main;
    static GomokuPreparationMenu gomokuPreparation;
    static GomokuMenu gomoku;
};


#endif //SUNNYCHESS_MENUMANAGER_H
