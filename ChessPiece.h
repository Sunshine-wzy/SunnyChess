#ifndef SUNNYCHESS_CHESSPIECE_H
#define SUNNYCHESS_CHESSPIECE_H

#include <graphics.h>


class ChessPiece {
private:
    COLORREF color;
    
public:
    explicit ChessPiece(COLORREF color);
    
    // 绘制棋子
    void draw(int x, int y, int radius) const;

    COLORREF getColor() const;
    
    bool isNone() const;
    bool isNotNone() const;
    
    
    static ChessPiece *none;
    static ChessPiece *black;
    static ChessPiece *white;
    static ChessPiece *red;
    static ChessPiece *yellow;
    static ChessPiece *blue;
    static ChessPiece *green;
    
};


#endif //SUNNYCHESS_CHESSPIECE_H
