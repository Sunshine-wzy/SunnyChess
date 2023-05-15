#include "ChessBoard.h"


ChessBoard::ChessBoard(int x, int y, int width, int height, int size)
        : startX(x), startY(y), width(width), height(height), size(size),
          slots(size + 1, std::vector<ChessSlot>(size + 1)),
          boardImage(IMAGE(height + 20, height + 20)),
          drawingImage(IMAGE()), round(ChessPiece::none) {
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

    Position position {};
    for (int n = 1; n <= size; n++) {
        for (int m = 1; m <= size; m++) {
            ChessPiece *piece = slots[n][m].getPiece();
            
            if (piece != nullptr) {
                if (piece->isNotNone()) {
                    setfillcolor(piece->getColor());
                    if (getCenterPositionByOrder(position, n, m))
                        piece->draw(position.x, position.y, 12);
                }
            }
        }
    }
}

bool ChessBoard::getCenterPositionByPosition(Position &position, int x, int y) const {
    if (!getOrderByPosition(position, x, y)) return false;
    
    return getCenterPositionByOrder(position, position.x, position.y);
}

bool ChessBoard::getOrderByPosition(Position &order, int x, int y) const {
    if (!isPositionInBoard(x, y)) return false;
    
    order.x = (x - startX) / (width / (size - 1)) + 1;
    order.y = (y - startY) / (height / (size - 1)) + 1;
    return true;
}

bool ChessBoard::getCenterPositionByOrder(Position &position, int x, int y) const {
    if (!isOrderInBoard(x, y))
        return false;
    
    position.x = startX + (x - 1) * width / (size - 1);
    position.y = startY + (y - 1) * height / (size - 1);
    return true;
}

bool ChessBoard::isOrderInBoard(int x, int y) const {
    return x >= 1 && x <= size && y >= 1 && y <= size;
}

bool ChessBoard::isPositionInBoard(int x, int y) const {
    return x >= startX && x <= startX + width && y >= startY && y <= startY + height;
}

bool ChessBoard::placePiece(ChessPiece *piece, int x, int y) {
    if (!isOrderInBoard(x, y))
        return false;

    if (slots[x][y].getPiece() != ChessPiece::none)
        return false;

    slots[x][y].setPiece(piece);
    return true;
}

bool ChessBoard::placePiece(ChessPiece *piece, Position &order) {
    return placePiece(piece, order.x, order.y);
}

void ChessBoard::init() {
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            slots[i][j].setPiece(ChessPiece::none);
        }
    }
}

ChessPiece *ChessBoard::getRound() const {
    return round;
}

void ChessBoard::setRound(ChessPiece *theRound) {
    round = theRound;
}
