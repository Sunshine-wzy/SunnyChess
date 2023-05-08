#include "ChessBoard.h"

ChessBoard::ChessBoard(int x, int y, int width, int height) : startX(x), startY(y), width(width), height(height),
                                                              boardImage(IMAGE(height + 20, height + 20)),
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

    loadimage(&boardImage, _T("../resources/chessboard.jpg"), 1600, 1600);

    setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 2);
    setlinecolor(BLACK);

    for (int x1 = startX, i = 0; i < 19; i++, x1 = startX + width * i / 18) {
        line(x1, startY, x1, startY + height);
    }

    for (int y1 = startY, j = 0; j < 19; j++, y1 = startY + height * j / 18) {
        line(startX, y1, startX + width, y1);
    }
    
    setfillcolor(BLACK);
    solidcircle(startX + width * 3 / 18, startY + height * 3 / 18, POINT_SIZE);
    solidcircle(startX + width * 9 / 18, startY + height * 3 / 18, POINT_SIZE);
    solidcircle(startX + width * 15 / 18, startY + height * 3 / 18, POINT_SIZE);
    solidcircle(startX + width * 3 / 18, startY + height * 9 / 18, POINT_SIZE);
    solidcircle(startX + width * 9 / 18, startY + height * 9 / 18, POINT_SIZE);
    solidcircle(startX + width * 15 / 18, startY + height * 9 / 18, POINT_SIZE);
    solidcircle(startX + width * 3 / 18, startY + height * 15 / 18, POINT_SIZE);
    solidcircle(startX + width * 9 / 18, startY + height * 15 / 18, POINT_SIZE);
    solidcircle(startX + width * 15 / 18, startY + height * 15 / 18, POINT_SIZE);
}

void ChessBoard::drawPieces() {
    SetWorkingImage(&drawingImage);
    drawingImage = boardImage;


}

bool ChessBoard::getPositionByPosition(Position *position, int x, int y) {
    
    position = nullptr;
    return false;
}

bool ChessBoard::getOrderByPosition(Position *order, int x, int y) {
    
    order = nullptr;
    return false;
}

bool ChessBoard::getPositionByOrder(Position *position, int x, int y) {
    
    position = nullptr;
    return false;
}

bool ChessBoard::placePiece(ChessPiece &piece, int x, int y) {
    if (!isInBoard(x, y))
        return false;
    
    if (&slots[x][y].getPiece() != &ChessPiece::none)
        return false;
    
    slots[x][y].setPiece(piece);
    return true;
}

bool ChessBoard::placePiece(ChessPiece &piece, Position &order) {
    return placePiece(piece, order.x, order.y);
}

bool ChessBoard::isInBoard(int x, int y) {
    return x >= 1 && x <= 19 && y >= 1 && y <= 19;
}
