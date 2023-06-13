#ifndef SUNNYCHESS_GOMOKUMENU_H
#define SUNNYCHESS_GOMOKUMENU_H

#include "Menu.h"
#include "GomokuChessBoard.h"
#include "Game.h"
#include "CircleSelectionButton.h"
#include "RoundRectangleButton.h"
#include "DisplayButton.h"
#include <mutex>
#include <atomic>


class GomokuMenu : public Menu, public Game {
private:
    GomokuChessBoard *board;                    // 棋盘
    RECT timerArea;                             // 计时器区域
    int sidebarBaseX;                           // 侧边栏基础x坐标
    int sidebarCenterX;                         // 侧边栏中心x坐标
    
    CircleSelectionButton *buttonRetract;       // 悔棋按钮
    RoundRectangleButton *buttonForbidden;      // 禁止按钮
    DisplayKeyButton *buttonDisplayKey;         // 按键提示按钮
    RoundRectangleButton *buttonVictory;        // 胜利按钮

    IMAGE imageBackground;                      // 背景图片
    IMAGE imageVictory;                         // 胜利图片
    
    std::mutex mutexRedraw;                     // 重新绘制界面锁
    std::mutex mutexDrawTime;                   // 绘制计时锁
    
    std::atomic<int> playPieceDropSoundCount;   // 播放落子音效计数

public:
    GomokuMenu();

    ~GomokuMenu() override;

    void onOpenInit() override;
    
    void onInit() override;

    void onEnable() override;

    void startGame() override;

    void runGame(int x, int y) override;

    void endGame(int x, int y) override;

    void initButtons() override;

    // 重新绘制界面
    template <class Callable>
    void redraw(Callable &&callable, bool isRedraw = true);
    
    void redraw();
    
    // 绘制计时
    void drawTime(tm *time, RECT *rect);
    
    // 运行机器人
    void runBot(Bot &bot);
    
    // 计算评分
    void calculateScore(Bot &bot);
    
    // 获取机器人落子点
    Position botThink(Bot &bot);

};


template <class Callable>
void GomokuMenu::redraw(Callable &&callable, bool isRedraw) {
    const std::lock_guard<std::mutex> lock(mutexRedraw);

    BeginBatchDraw();

    if (isRedraw) {
        cleardevice();
        onInit();
        drawButtons();
    }
    
    callable();

    FlushBatchDraw();
}


#endif //SUNNYCHESS_GOMOKUMENU_H
