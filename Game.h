#ifndef SUNNYCHESS_GAME_H
#define SUNNYCHESS_GAME_H


class Game {
private:
    bool running;
    
public:
    explicit Game();


    // 开始游戏
    virtual void startGame() = 0;
    
    // 进行游戏
    virtual void runGame() = 0;
    
    // 结束游戏
    virtual void endGame() = 0;


    bool isRunning() const;

    void setRunning(bool running);
};


#endif //SUNNYCHESS_GAME_H
