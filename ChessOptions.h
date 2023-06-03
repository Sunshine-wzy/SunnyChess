#ifndef SUNNYCHESS_CHESSOPTIONS_H
#define SUNNYCHESS_CHESSOPTIONS_H

#include "ChessPiece.h"


class ChessOptions {
public:
    // 玩家数量
    int number;
    // player1 执子类型
    ChessPiece *type;
    // 棋盘大小
    int size;
    
    
    ChessOptions();
    
    virtual ~ChessOptions();
    
};


class GomokuOptions : public ChessOptions {
public:
    enum class Mode {
        FRIEND, BOT
    };
    
    Mode mode;
    
    GomokuOptions();
    
};


#endif //SUNNYCHESS_CHESSOPTIONS_H
