#ifndef SUNNYCHESS_GOMOKUPREPARATIONMENU_H
#define SUNNYCHESS_GOMOKUPREPARATIONMENU_H

#include "Menu.h"
#include "GomokuMenu.h"


class GomokuPreparationMenu : public Menu {
private:


public:
    GomokuPreparationMenu();

    void onInit() override;

    void onEnable() override;

    void initButtons() override;


};


#endif //SUNNYCHESS_GOMOKUPREPARATIONMENU_H
