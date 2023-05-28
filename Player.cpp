#include "Player.h"
#include "graphics.h"

Player::Player(ChessPiece *piece, int selectionBoxHalfWidth, int selectionBoxHalfHeight)
            : piece(piece),
              selectionBoxHalfWidth(selectionBoxHalfWidth),
              selectionBoxHalfHeight(selectionBoxHalfHeight) {}

void Player::drawSelectionBox(int x, int y) {
//    setcolor(0x9FC57);
    setcolor(piece->getColor());
    setlinestyle(PS_DASH | PS_ENDCAP_SQUARE);
    rectangle(x - selectionBoxHalfWidth, y - selectionBoxHalfHeight, x + selectionBoxHalfWidth, y + selectionBoxHalfHeight);
}
