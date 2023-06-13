#ifndef SUNNYCHESS_PLAYER_H
#define SUNNYCHESS_PLAYER_H

#include "ChessPiece.h"
#include "Position.h"
#include <graphics.h>
#include <string>
#include <vector>


// 玩家 (表示参与对局的一方)
class Player {
private:
    // 执子类型
    ChessPiece *piece;
    
    // 选择框大小
    int selectionBoxHalfWidth;
    int selectionBoxHalfHeight;

public:
    // 选择框位置序号
    Position selectionBoxOrder;
    
    
    Player(ChessPiece *piece, int selectionBoxHalfWidth, int selectionBoxHalfHeight);

    // 绘制选择框
    virtual void drawSelectionBox(int x, int y);
    
    // 触发绘制选择框事件
    virtual void onSelectionBoxDraw(const Position &position, const Position &order);
    
    ChessPiece *getPiece() const;

    int getSelectionBoxHalfWidth() const;

    int getSelectionBoxHalfHeight() const;

};


// 按键设置
struct KeySettings {
    BYTE up;            // 上
    BYTE down;          // 下
    BYTE left;          // 左
    BYTE right;         // 右
    BYTE drop;          // 落子
    
    std::string keys[5];

    
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
    // 按键设置
    KeySettings keySettings;
    
public:
    User(ChessPiece *piece, int selectionBoxHalfWidth, int selectionBoxHalfHeight, KeySettings keySettings);


    const KeySettings &getKeySettings() const;
    
};


// 机器人 (表示电脑玩家)
class Bot : public Player {
private:
    // 对弈玩家
    User &user;
    
public:
    // 评分表
    std::vector<std::vector<int>> scoreMap;
    
    
    Bot(ChessPiece *piece, User &user, int selectionBoxHalfWidth, int selectionBoxHalfHeight);

    User &getUser() const;

};


#endif //SUNNYCHESS_PLAYER_H
