#include <graphics.h>
#include <conio.h>

#include "MenuManager.h"


int main() {
    // 初始化图形模式
    initgraph(MainMenu::WIDTH, MainMenu::HEIGHT);
    
    // 打开主菜单
    MenuManager::main.open();
    
    _getch();
    
    // 关闭图形模式
    closegraph();
    
    return 0;
}
