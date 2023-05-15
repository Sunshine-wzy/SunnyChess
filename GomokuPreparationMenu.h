#ifndef SUNNYCHESS_GOMOKUPREPARATIONMENU_H
#define SUNNYCHESS_GOMOKUPREPARATIONMENU_H

#include "GomokuMenu.h"
#include "SelectionButtonGroup.h"


class GomokuPreparationMenu : public Menu {
private:
    SelectionButtonGroup chessTypeSelectionGroup;

public:
    GomokuPreparationMenu();

    void onInit() override;

    void onEnable() override;

    void initButtons() override;


};


#endif //SUNNYCHESS_GOMOKUPREPARATIONMENU_H
