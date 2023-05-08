#include "ChessPiece.h"

ChessPiece::ChessPiece(COLORREF color) : color(color) {}

ChessPiece ChessPiece::none = ChessPiece(0);

ChessPiece ChessPiece::black = ChessPiece(BLACK);

ChessPiece ChessPiece::white = ChessPiece(WHITE);

void ChessPiece::draw(int x, int y, int radius) {
    
}
