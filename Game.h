#ifndef SUNNYCHESS_GAME_H
#define SUNNYCHESS_GAME_H

#include "Timer.h"


class Game {
private:
    bool running;
    Timer timer;
    
public:
    explicit Game();


    // 开始游戏
    virtual void startGame() = 0;
    
    // 进行游戏
    virtual void runGame(int x, int y) = 0;
    
    // 结束游戏
    virtual void endGame(int x, int y) = 0;


    bool isRunning() const;

    void setRunning(bool running);
    
    const bool *getRunning();

    Timer &getTimer();
    
};


#endif //SUNNYCHESS_GAME_H
