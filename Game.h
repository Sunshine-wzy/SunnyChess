#ifndef SUNNYCHESS_GAME_H
#define SUNNYCHESS_GAME_H

#include "Timer.h"


class Game {
private:
    bool running;           // 是否正在进行游戏
    Timer timer;            // 计时器
    
public:
    explicit Game();


    // 开始游戏
    virtual void startGame() = 0;
    
    // 进行游戏
    virtual void runGame(int x, int y) = 0;
    
    // 结束游戏
    virtual void endGame(int x, int y) = 0;


    // 获取游戏是否正在进行
    bool isRunning() const;

    // 设置游戏进行状态
    void setRunning(bool running);
    
    const bool *getRunning();

    // 获取计时器
    Timer &getTimer();
    
};


#endif //SUNNYCHESS_GAME_H
