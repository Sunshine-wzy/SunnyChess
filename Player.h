#ifndef SUNNYCHESS_PLAYER_H
#define SUNNYCHESS_PLAYER_H

#include "ChessPiece.h"


// 玩家 (表示参与对局的一方)
class Player {
private:
    ChessPiece *piece;
    
    int selectionBoxHalfWidth;
    int selectionBoxHalfHeight;
    
    
public:
    Player(ChessPiece *piece, int selectionBoxHalfWidth, int selectionBoxHalfHeight);

    virtual void drawSelectionBox(int x, int y);

};


// 用户 (表示人类玩家)
class User : public Player {
    
};


// 机器人 (表示电脑玩家)
class Bot : public Player {
    
};


#endif //SUNNYCHESS_PLAYER_H
