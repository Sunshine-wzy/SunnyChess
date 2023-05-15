#include "ChessSlot.h"

ChessSlot::ChessSlot() : piece(ChessPiece::none) {}

ChessPiece *ChessSlot::getPiece() {
    return piece;
}

void ChessSlot::setPiece(ChessPiece *thePiece) {
    this->piece = thePiece;
}
