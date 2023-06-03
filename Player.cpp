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

KeySettings KeySettings::none = {0x07, 0x07, 0x07, 0x07, 0x07};
KeySettings KeySettings::wsadq = {0x57, 0x53, 0x41, 0x44, 0x51};
KeySettings KeySettings::udlrm = {VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, 0x4D};
KeySettings KeySettings::yhgjt = {0x59, 0x48, 0x47, 0x4A, 0x54};
KeySettings KeySettings::pslqo = {0x50, VK_OEM_1, 0x4C, VK_OEM_7, 0x4F};
KeySettings KeySettings::n85467 = {VK_NUMPAD8, VK_NUMPAD5, VK_NUMPAD4, VK_NUMPAD6, VK_NUMPAD7};

KeySettings *KeySettings::defaultSettings[7] = {
        &KeySettings::none, &KeySettings::wsadq, &KeySettings::udlrm,
        &KeySettings::yhgjt, &KeySettings::pslqo, &KeySettings::n85467,
        &KeySettings::none
};

User::User(ChessPiece *piece, int selectionBoxHalfWidth, int selectionBoxHalfHeight, KeySettings keySettings)
            : Player(piece, selectionBoxHalfWidth, selectionBoxHalfHeight),
              keySettings(keySettings) {}

const KeySettings &User::getKeySettings() const {
    return keySettings;
}

Bot::Bot(ChessPiece *piece, int selectionBoxHalfWidth, int selectionBoxHalfHeight)
            : Player(piece, selectionBoxHalfWidth, selectionBoxHalfHeight) {}