#include "ChessBoard.h"


ChessBoard::ChessBoard(int x, int y, int width, int height, int size)
        : startX(x), startY(y), width(width), height(height), size(size),
          slots(size + 1, std::vector<ChessSlot>(size + 1)),
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

    setlinecolor(BLACK);

    setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 2);
    line(startX, startY, startX, startY + height);
    line(startX + width, startY, startX + width, startY + height);
    line(startX, startY, startX + width, startY);
    line(startX, startY + height, startX + width, startY + height);

    setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 1);
    for (int x1 = startX, i = 0; i < size - 1; i++, x1 = startX + width * i / (size - 1)) {
        line(x1, startY, x1, startY + height);
    }
    for (int y1 = startY, j = 0; j < size - 1; j++, y1 = startY + height * j / (size - 1)) {
        line(startX, y1, startX + width, y1);
    }

    setfillcolor(BLACK);
    solidcircle(startX + width * 3 / (size - 1), startY + height * 3 / (size - 1), POINT_SIZE);
    solidcircle(startX + width * 9 / (size - 1), startY + height * 3 / (size - 1), POINT_SIZE);
    solidcircle(startX + width * 15 / (size - 1), startY + height * 3 / (size - 1), POINT_SIZE);
    solidcircle(startX + width * 3 / (size - 1), startY + height * 9 / (size - 1), POINT_SIZE);
    solidcircle(startX + width * 9 / (size - 1), startY + height * 9 / (size - 1), POINT_SIZE);
    solidcircle(startX + width * 15 / (size - 1), startY + height * 9 / (size - 1), POINT_SIZE);
    solidcircle(startX + width * 3 / (size - 1), startY + height * 15 / (size - 1), POINT_SIZE);
    solidcircle(startX + width * 9 / (size - 1), startY + height * 15 / (size - 1), POINT_SIZE);
    solidcircle(startX + width * 15 / (size - 1), startY + height * 15 / (size - 1), POINT_SIZE);
}

void ChessBoard::drawPieces() {
    slots[3][3].setPiece(ChessPiece::white);

    SetWorkingImage(&drawingImage);
    drawingImage = boardImage;
    for (int n = 0; n < size; n++) {
        for (int m = 0; m < size; m++) {
            ChessPiece piece = slots[n][m].getPiece();
            if (piece.getColor() != 0) {
                int x = startX + n * width / (size - 1);
                int y = startY + m * height / (size - 1);
                int radius = 8;
                piece.draw(x, y, radius);
            }
        }
    }
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

bool ChessBoard::isInBoard(int x, int y) const {
    return x >= 1 && x <= size && y >= 1 && y <= size;
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

void ChessBoard::init() {
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            slots[i][j].setPiece(ChessPiece::none);
        }
    }
}
