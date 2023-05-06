#include "ChessBoard.h"

ChessBoard::ChessBoard(int x, int y, int width, int height) : startX(x), startY(y), width(width), height(height),
                                                              boardImage(IMAGE(height - 200, height -200)), drawingImage(IMAGE()) {
    drawBoard();
}

void ChessBoard::draw() {
    drawPieces();

    SetWorkingImage();
    putimage(startX, startY, &drawingImage, SRCAND);
}

void ChessBoard::drawBoard() {
    SetWorkingImage(&boardImage);
    
    
}

void ChessBoard::drawPieces() {
    SetWorkingImage(&drawingImage);
    drawingImage = boardImage;
    
    
}

bool ChessBoard::getPosition(Position *position, int x, int y) {
    
    
    position = nullptr;
    return false;
}
