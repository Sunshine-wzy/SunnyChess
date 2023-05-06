#include <graphics.h>
#include <conio.h>

#include "MainMenu.h"


int main() {
    MainMenu mainMenu;
    
    // 初始化主菜单
    mainMenu.init();
    
    _getch();
    
    // 关闭图形模式
    closegraph();
    
    return 0;
}
