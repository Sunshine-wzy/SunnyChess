#include "ChessBoard.h"


ChessBoard::ChessBoard(int x, int y, int width, int height, int size)
        : startX(x), startY(y), baseX(30), baseY(30),
          width(width), height(height), extraHeight(60), extraWidth(60), size(size),
          slotWidth((double) width / (size - 1)), slotHeight((double) height / (size - 1)),
          totalWidth(width + extraWidth), totalHeight(height + extraHeight),
          slots(size + 1, std::vector<ChessSlot>(size + 1)),
          boardImage(IMAGE(totalWidth, totalHeight)),
          drawingImage(IMAGE(totalWidth, totalHeight)), round(ChessPiece::none) {
    drawBoard();
}

void ChessBoard::draw() {
    drawPieces();

    putimage(startX, startY, &drawingImage, SRCPAINT);
}

void ChessBoard::drawBoard() {
    SetWorkingImage(&boardImage);

    loadimage(&boardImage, _T("../resources/chessboard.jpg"), totalWidth, totalHeight);

    setlinecolor(BLACK);

    setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 2);
    line(baseX, baseY, baseX, baseY + height);
    line(baseX + width, baseY, baseX + width, baseY + height);
    line(baseX, baseY, baseX + width, baseY);
    line(baseX, baseY + height, baseX + width, baseY + height);

    setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 1);
    for (int x1 = baseX, i = 0; i < size - 1; i++, x1 = baseX + (int) (i * slotWidth)) {
        line(x1, baseY, x1, baseY + height);
    }
    for (int y1 = baseY, j = 0; j < size - 1; j++, y1 = baseY + (int) (j * slotHeight)) {
        line(baseX, y1, baseX + width, y1);
    }

    setfillcolor(BLACK);
    solidcircle(baseX + (int) (slotWidth * 3), baseY + (int) (slotHeight * 3), POINT_SIZE);
    solidcircle(baseX + (int) (slotWidth * 9), baseY + (int) (slotHeight * 3), POINT_SIZE);
    solidcircle(baseX + (int) (slotWidth * 15), baseY + (int) (slotHeight * 3), POINT_SIZE);
    solidcircle(baseX + (int) (slotWidth * 3), baseY + (int) (slotHeight * 9), POINT_SIZE);
    solidcircle(baseX + (int) (slotWidth * 9), baseY + (int) (slotHeight * 9), POINT_SIZE);
    solidcircle(baseX + (int) (slotWidth * 15), baseY + (int) (slotHeight * 9), POINT_SIZE);
    solidcircle(baseX + (int) (slotWidth * 3), baseY + (int) (slotHeight * 15), POINT_SIZE);
    solidcircle(baseX + (int) (slotWidth * 9), baseY + (int) (slotHeight * 15), POINT_SIZE);
    solidcircle(baseX + (int) (slotWidth * 15), baseY + (int) (slotHeight * 15), POINT_SIZE);

    settextcolor(WHITE);
    settextstyle(20,10,_T("Consolas"));
    for(int i=0;i<19;i++)
    {
        RECT r={baseX-20, baseY+10+(18-i)*slotHeight, baseX, baseY-10+(18-i)*slotHeight};
        drawtext(_T(numberToString(i+1).c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }
    for(int i=0;i<19;i++)
    {
        RECT r={baseX-10+i*slotWidth, baseY+18*slotHeight+5, baseX+10+i*slotWidth, baseY+18*slotHeight+25};
        drawtext(_T(numberToString(i+100).c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }
    SetWorkingImage();
}

void ChessBoard::drawPieces() {
    slots[3][3].setPiece(ChessPiece::white);

    SetWorkingImage(&drawingImage);
    drawingImage = boardImage;

    Position position{};
    for (int n = 1; n <= size; n++) {
        for (int m = 1; m <= size; m++) {
            ChessPiece *piece = slots[n][m].getPiece();

            if (piece != nullptr) {
                if (piece->isNotNone()) {
                    setfillcolor(piece->getColor());
                    if (getCenterPositionByOrder(position, n, m))
                        piece->draw(position.x - startX, position.y - startY, 12);
                }
            }
        }
    }

    SetWorkingImage();
}

std::string ChessBoard::numberToString(int number) {
    std::string str;

    if(number<=9&&number>=0) {
        str.push_back('0' + number);
    } else if(number>9&&number<100) {
        int a=number/10;
        number=number%10;

        str.push_back('0'+a);
        str.push_back('0'+number);
    }
    else {
         str.push_back('A'+number-100);
    }

    return str;
}

bool ChessBoard::getCenterPositionByPosition(Position &position, int x, int y) const {
    if (!getOrderByPosition(position, x, y)) return false;

    return getCenterPositionByOrder(position, position.x, position.y);
}

bool ChessBoard::getOrderByPosition(Position &order, int x, int y) const {
    if (!isPositionInBoard(x, y)) return false;

    order.x = (int) ((x - startX - baseX + slotWidth / 2) / slotWidth) + 1;
    order.y = (int) ((y - startY - baseY + slotHeight / 2) / slotHeight) + 1;
    if (!isOrderInBoard(order.x, order.y)) return false;
    
    return true;
}

bool ChessBoard::getCenterPositionByOrder(Position &position, int x, int y) const {
    if (!isOrderInBoard(x, y))
        return false;

    position.x = (int) (startX + baseX + (x - 1) * slotWidth);
    position.y = (int) (startY + baseY + (y - 1) * slotHeight);
    return true;
}

bool ChessBoard::isOrderInBoard(int x, int y) const {
    return x >= 1 && x <= size && y >= 1 && y <= size;
}

bool ChessBoard::isPositionInBoard(int x, int y) const {
    return x >= startX && x <= startX + totalWidth && y >= startY && y <= startY + totalHeight;
}

bool ChessBoard::placePiece(ChessPiece *piece, int x, int y) {
    if (!isOrderInBoard(x, y))
        return false;

    if (slots[x][y].getPiece() != nullptr && slots[x][y].getPiece() != ChessPiece::none)
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

int ChessBoard::getStartX() const {
    return startX;
}

int ChessBoard::getStartY() const {
    return startY;
}

int ChessBoard::getBaseX() const {
    return baseX;
}

int ChessBoard::getBaseY() const {
    return baseY;
}

int ChessBoard::getWidth() const {
    return width;
}

int ChessBoard::getHeight() const {
    return height;
}

int ChessBoard::getExtraWidth() const {
    return extraWidth;
}

int ChessBoard::getExtraHeight() const {
    return extraHeight;
}

int ChessBoard::getSize() const {
    return size;
}

double ChessBoard::getSlotWidth() const {
    return slotWidth;
}

double ChessBoard::getSlotHeight() const {
    return slotHeight;
}

int ChessBoard::getTotalWidth() const {
    return totalWidth;
}

int ChessBoard::getTotalHeight() const {
    return totalHeight;
}
