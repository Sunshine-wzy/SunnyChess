#ifndef SUNNYCHESS_PLAYER_H
#define SUNNYCHESS_PLAYER_H

#include "ChessPiece.h"
#include "Position.h"
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
    
    virtual void onSelectionBoxDraw(const Position &position, const Position &order);
    
    ChessPiece *getPiece() const;

    int getSelectionBoxHalfWidth() const;

    int getSelectionBoxHalfHeight() const;

};


struct KeySettings {
    BYTE up;            // 上
    BYTE down;          // 下
    BYTE left;          // 左
    BYTE right;         // 右
    BYTE drop;          // 落子
    
    wchar_t keys[5];

    
    static KeySettings none;            // 无
    static KeySettings wsadq;           // WSADQ
    static KeySettings udlrm;           // 上下左右M
    static KeySettings yhgjt;           // YHGJT
    static KeySettings pslqo;           // P;L'O
    static KeySettings n85467;          // 小键盘85467
    
    static KeySettings *defaultSettings[7];
};


// 用户 (表示人类玩家)
class User : public Player {
private:
    KeySettings keySettings;
    
public:
    User(ChessPiece *piece, int selectionBoxHalfWidth, int selectionBoxHalfHeight, KeySettings keySettings);


    const KeySettings &getKeySettings() const;
    
};


// 机器人 (表示电脑玩家)
class Bot : public Player {
public:
    Bot(ChessPiece *piece, int selectionBoxHalfWidth, int selectionBoxHalfHeight);
    
};


#endif //SUNNYCHESS_PLAYER_H
