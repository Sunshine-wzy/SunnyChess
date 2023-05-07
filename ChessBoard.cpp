#include "ChessBoard.h"

ChessBoard::ChessBoard(int x, int y, int width, int height) : startX(x), startY(y), width(width), height(height),
                                                              boardImage(IMAGE(height - 200, height - 200)),
                                                              drawingImage(IMAGE()) {
    drawBoard();
}

void ChessBoard::draw() {
    drawPieces();

    SetWorkingImage();
    putimage(startX, startY, &drawingImage, SRCPAINT);
}

void ChessBoard::drawBoard() {
    SetWorkingImage(&boardImage);
//    setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 2);

    for (int x1 = startX; x1 <= startX + width; x1 += (width + startX) / 18) {
        line(x1, startY, x1, startY + height);
    }
    
    for (int y1 = startY; y1 <= startY + height; y1 += (height + startY) / 18) {
        line(startX, y1, startX + width, y1);
    }
}

void ChessBoard::drawPieces() {
    SetWorkingImage(&drawingImage);
    drawingImage = boardImage;


}

bool ChessBoard::getPosition(Position *position, int x, int y) {


    position = nullptr;
    return false;
}
