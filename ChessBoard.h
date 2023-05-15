#ifndef SUNNYCHESS_CHESSBOARD_H
#define SUNNYCHESS_CHESSBOARD_H

#include "ChessSlot.h"
#include "Position.h"
#include <vector>


class ChessBoard {
protected:
    // 格子
    std::vector<std::vector<ChessSlot> > slots;

private:
    int startX;             // 左上角x坐标
    int startY;             // 左上角y坐标
    int width;              // 宽
    int height;             // 高

    int size;               // 行列数

    IMAGE boardImage;       // 棋盘背景以及基础格子
    IMAGE drawingImage;     // 包括棋子的棋盘

    ChessPiece *round;
    
public:
    ChessBoard(int x, int y, int width, int height, int size);

    // 画出整个棋盘（基础格子+棋子）
    void draw();

    // 画出棋盘的基础格子
    void drawBoard();

    // 画出棋子
    void drawPieces();

    // 根据坐标(x, y)获取格子中心点坐标
    // 若(x, y)不在任何一个格子内，则返回false
    bool getCenterPositionByPosition(Position &position, int x, int y) const;

    // 根据坐标(x, y)获取格子序号
    bool getOrderByPosition(Position &order, int x, int y) const;

    // 根据序号(x, y)获取格子中心点坐标
    bool getCenterPositionByOrder(Position &position, int x, int y) const;

    // 序号(x, y)是否在棋盘内
    bool isOrderInBoard(int x, int y) const;

    // 坐标(x, y)是否在棋盘内
    bool isPositionInBoard(int x, int y) const;


    // 初始化棋盘
    virtual void init();

    // 尝试向序号(x, y)放置棋子
    virtual bool placePiece(ChessPiece *piece, int x, int y);

    virtual bool placePiece(ChessPiece *piece, Position &order);

    // 胜利判定 落子时触发
    virtual bool judge(int x, int y) = 0;


    ChessPiece *getRound() const;

    void setRound(ChessPiece *round);


    // 点大小
    static const int POINT_SIZE = 6;
};


#endif //SUNNYCHESS_CHESSBOARD_H
