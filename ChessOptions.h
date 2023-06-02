#ifndef SUNNYCHESS_CHESSOPTIONS_H
#define SUNNYCHESS_CHESSOPTIONS_H

#include "ChessPiece.h"


class ChessOptions {
public:
    // player1 执子类型
    ChessPiece *type;
    // 棋盘大小
    int size;
    // 玩家数量
    int number;
    
    
    ChessOptions();
    
    virtual ~ChessOptions();
    
};


class GomokuOptions : public ChessOptions {
private:
    
    
public:
    GomokuOptions();
    
};


#endif //SUNNYCHESS_CHESSOPTIONS_H
