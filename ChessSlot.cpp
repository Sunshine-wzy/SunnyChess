#include "ChessSlot.h"

ChessSlot::ChessSlot() : piece(ChessPiece::none) {}

ChessPiece ChessSlot::getPiece() const {
    return piece;
}
