#include "Player.h"

Player::Player(ChessPiece *piece, int selectionBoxHalfWidth, int selectionBoxHalfHeight)
            : piece(piece),
              selectionBoxHalfWidth(selectionBoxHalfWidth),
              selectionBoxHalfHeight(selectionBoxHalfHeight),
              selectionBoxOrder(Position {0, 0}) {}

void Player::drawSelectionBox(int x, int y) {
//    setcolor(0x9FC57);
    setcolor(piece->getColor());
    setlinestyle(PS_DASH | PS_ENDCAP_SQUARE);
    rectangle(x - selectionBoxHalfWidth, y - selectionBoxHalfHeight, x + selectionBoxHalfWidth, y + selectionBoxHalfHeight);
}

void Player::onSelectionBoxDraw(const Position &position, const Position &order) {
    // 画出选择框
    drawSelectionBox(position.x, position.y);
    // 更新选择框位置序号
    selectionBoxOrder = order;
}

ChessPiece *Player::getPiece() const {
    return piece;
}

int Player::getSelectionBoxHalfWidth() const {
    return selectionBoxHalfWidth;
}

int Player::getSelectionBoxHalfHeight() const {
    return selectionBoxHalfHeight;
}

User::User(ChessPiece *piece, int selectionBoxHalfWidth, int selectionBoxHalfHeight, KeySettings keySettings)
            : Player(piece, selectionBoxHalfWidth, selectionBoxHalfHeight),
              keySettings(keySettings) {}

const KeySettings &User::getKeySettings() const {
    return keySettings;
}
