#ifndef SUNNYCHESS_GOMOKUPREPARATIONMENU_H
#define SUNNYCHESS_GOMOKUPREPARATIONMENU_H

#include "GomokuMenu.h"
#include "ChessOptions.h"
#include "SelectionButtonGroup.h"


class GomokuPreparationMenu : public Menu {
private:
    GomokuOptions options;
    
    SelectionButtonGroup chessTypeSelectionGroup;

public:
    GomokuPreparationMenu();

    void onInit() override;

    void onEnable() override;

    void initButtons() override;

    const GomokuOptions &getOptions() const;

};


#endif //SUNNYCHESS_GOMOKUPREPARATIONMENU_H
