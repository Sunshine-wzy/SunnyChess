#include "MenuManager.h"
#include <graphics.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")           // 加载静态库


int main() {
    // 初始化图形模式
    initgraph(MainMenu::WIDTH, MainMenu::HEIGHT);
    
    // 打开主菜单
    MenuManager::main.open();
    
    // 关闭图形模式
    closegraph();

    // 关闭音频文件
    mciSendString("close ../resources/piece_drop_sound.mp3", nullptr, 0, nullptr);
    mciSendString("close ../resources/victory_sound.mp3", nullptr, 0, nullptr);


    return 0;
}
