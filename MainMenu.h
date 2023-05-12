#ifndef SUNNYCHESS_MAINMENU_H
#define SUNNYCHESS_MAINMENU_H

#include <graphics.h>
#include "Menu.h"

// 主菜单
class MainMenu : public Menu {
private:
    // 线条样式
    LINESTYLE lineStyle;
    
public:
    MainMenu();

    void onInit() override;
    void initButtons() override;
    void onEnable() override;


    LINESTYLE& getLineStyle();


    // 窗口大小
    static const int WIDTH = 1000;
    static const int HEIGHT = 800;
};


#endif //SUNNYCHESS_MAINMENU_H
