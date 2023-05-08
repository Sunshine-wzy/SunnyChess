#ifndef SUNNYCHESS_GAME_H
#define SUNNYCHESS_GAME_H


class Game {
public:
    // 开始游戏
    virtual void startGame() = 0;
    
    // 进行游戏
    virtual void runGame() = 0;
};


#endif //SUNNYCHESS_GAME_H
