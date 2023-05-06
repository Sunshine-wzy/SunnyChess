#ifndef SUNNYCHESS_GOMOKUMENU_H
#define SUNNYCHESS_GOMOKUMENU_H

#include "Menu.h"


class GomokuMenu : public Menu {
    
    
public:
    GomokuMenu();

    void onInit() override;
    void onEnable() override;

};


#endif //SUNNYCHESS_GOMOKUMENU_H
