#ifndef SUNNYCHESS_CHESSPIECE_H
#define SUNNYCHESS_CHESSPIECE_H

#include <graphics.h>

class ChessPiece {
private:
    COLORREF color;
    
public:
    ChessPiece(COLORREF color);
    
    // 绘制棋子
    void draw(int x, int y, int radius);
    
    
    static ChessPiece none;
    static ChessPiece black;
    static ChessPiece white;
};


#endif //SUNNYCHESS_CHESSPIECE_H
