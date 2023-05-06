#ifndef SUNNYCHESS_MAINMENU_H
#define SUNNYCHESS_MAINMENU_H

#include <graphics.h>

// 主菜单
class MainMenu {
private:
    // 线条样式
    LINESTYLE lineStyle;
    
public:
    MainMenu();
    
    // 初始化主菜单
    void init();
    
    // 绘制按钮
    void drawButtons();
    // 绘制选择按钮
    void drawSelectingButton(int x, int y);
    
    LINESTYLE& getLineStyle();
    
    
    // 窗口大小
    static const int WIDTH = 1000;
    static const int HEIGHT = 800;
};


#endif //SUNNYCHESS_MAINMENU_H
