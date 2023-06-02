#ifndef SUNNYCHESS_PLAYER_H
#define SUNNYCHESS_PLAYER_H

#include "ChessBoard.h"
#include "Menu.h"
#include <graphics.h>


// 玩家 (表示参与对局的一方)
class Player {
private:
    ChessPiece *piece;
    
    int selectionBoxHalfWidth;
    int selectionBoxHalfHeight;

public:
    // 选择框位置序号
    Position selectionBoxOrder;
    
    
    Player(ChessPiece *piece, int selectionBoxHalfWidth, int selectionBoxHalfHeight);

    virtual void drawSelectionBox(int x, int y);
    
    ChessPiece *getPiece() const;

    int getSelectionBoxHalfWidth() const;

    int getSelectionBoxHalfHeight() const;

};


struct KeySettings {
    BYTE up;
    BYTE down;
    BYTE left;
    BYTE right;
    BYTE drop;
};


// 用户 (表示人类玩家)
class User : public Player {
private:
    KeySettings keySettings;
    
public:
    User(ChessPiece *piece, int selectionBoxHalfWidth, int selectionBoxHalfHeight, KeySettings keySettings);
    
    void onExMessage(ExMessage &message, ChessBoard &board, Menu &menu);
};


// 机器人 (表示电脑玩家)
class Bot : public Player {
    
};


#endif //SUNNYCHESS_PLAYER_H
