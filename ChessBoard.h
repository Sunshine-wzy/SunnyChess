#ifndef SUNNYCHESS_CHESSBOARD_H
#define SUNNYCHESS_CHESSBOARD_H

#include "ChessSlot.h"
#include "Position.h"

#define CHESSBOARD_SIZE 19


class ChessBoard {
protected:
    ChessSlot slots[CHESSBOARD_SIZE + 1][CHESSBOARD_SIZE + 1];
    
private:
    int startX;
    int startY;
    int width;
    int height;
    
    IMAGE boardImage;
    IMAGE drawingImage;
    
public:
    ChessBoard(int x, int y, int width, int height);

    // 画出整个棋盘（基础格子+棋子）
    void draw();
    // 画出棋盘的基础格子
    void drawBoard();
    // 画出棋子
    void drawPieces();
    
    // 根据坐标(x, y)获取格子中心点坐标
    // 若(x, y)不在任何一个格子内，则令position = nullptr并返回false
    bool getPositionByPosition(Position *position, int x, int y);
    // 根据坐标(x, y)获取格子序号
    bool getOrderByPosition(Position *order, int x, int y);
    // 根据序号(x, y)获取格子中心点坐标
    bool getPositionByOrder(Position *position, int x, int y);
    
    // 尝试向序号(x, y)放置棋子
    virtual bool placePiece(ChessPiece &piece, int x, int y);
    virtual bool placePiece(ChessPiece &piece, Position &order);
    
    // 胜利判定 落子时触发
    virtual bool judge(int x, int y) = 0;
    
    
    // 点大小
    static const int POINT_SIZE = 7;
    
    // 序号(x, y)是否在棋盘内
    static bool isInBoard(int x, int y);
};


#endif //SUNNYCHESS_CHESSBOARD_H
