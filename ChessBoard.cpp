#include "ChessBoard.h"

ChessBoard::ChessBoard(int x, int y, int width, int height) : startX(x), startY(y), width(width), height(height),
                                                              boardImage(IMAGE(height+20 , height+20 )),
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
    setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 2);
    loadimage(&boardImage, _T("\\Users\\86130\\Documents\\C++\\Workspace\\SunnyChess\\resources\\chessboard.jpg"), 1600, 1600);
    setlinecolor(BLACK);
    for (int x1 = startX,i=0; x1 <= startX + width;x1 = startX + width*i/18,i++) {
        line(x1, startY, x1, startY + height);
    }
    
    for (int y1 = startY,j=0; y1 <= startY + height;y1 = startY + height*j/18,j++) {
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
