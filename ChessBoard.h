#ifndef SUNNYCHESS_CHESSBOARD_H
#define SUNNYCHESS_CHESSBOARD_H

#include "ChessSlot.h"
#include "Position.h"

#define CHESSBOARD_SIZE 19


class ChessBoard {
private:
    ChessSlot slots[CHESSBOARD_SIZE][CHESSBOARD_SIZE];
    
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
    
    // 根据给定的x和y获取格子坐标
    // 若(x, y)不在任何一个格子内，则令position = nullptr并返回false
    bool getPosition(Position *position, int x, int y);
};


#endif //SUNNYCHESS_CHESSBOARD_H
