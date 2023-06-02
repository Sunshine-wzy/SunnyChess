#include "Player.h"
#include "graphics.h"

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

void User::onExMessage(ExMessage &message, ChessBoard &board, Menu &menu) {
    Position pos {};
    
    switch (message.message) {
        // 鼠标移动
        case WM_MOUSEMOVE:
            if (board.getCenterPositionByPosition(pos, message.x, message.y)) {
                BeginBatchDraw();
                menu.redraw();

                // 画出选择框
                drawSelectionBox(pos.x, pos.y);
                // 更新选择框位置序号
                if (board.getOrderByPosition(pos, message.x, message.y)) {
                    selectionBoxOrder = pos;
                }

                FlushBatchDraw();
            }
            break;
        
        // 按键按下
        case WM_KEYDOWN:
            if (message.vkcode == keySettings.up) {
                
            } else if (message.vkcode == keySettings.down) {
                
            } else if (message.vkcode == keySettings.left) {
                
            } else if (message.vkcode == keySettings.right) {
                
            }
            break;
    }
}
