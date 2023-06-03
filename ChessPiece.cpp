#include "ChessPiece.h"

ChessPiece::ChessPiece(COLORREF color) : color(color) {}

ChessPiece *ChessPiece::none = new ChessPiece(0);

ChessPiece *ChessPiece::black = new ChessPiece(BLACK);

ChessPiece *ChessPiece::white = new ChessPiece(WHITE);

ChessPiece *ChessPiece::red = new ChessPiece(RED);

ChessPiece *ChessPiece::yellow = new ChessPiece(YELLOW);

ChessPiece *ChessPiece::blue = new ChessPiece(BLUE);

ChessPiece *ChessPiece::green = new ChessPiece(GREEN);

void ChessPiece::draw(int x, int y, int radius) const {
    if (isNone()) return;
    
    setcolor(color);
    solidcircle(x, y, radius);
}

COLORREF ChessPiece::getColor() const {
    return color;
}

bool ChessPiece::isNone() const {
    return this == none;
}

bool ChessPiece::isNotNone() const {
    return this != none;
}
