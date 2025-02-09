#ifndef SUNNYCHESS_CHESSSLOT_H
#define SUNNYCHESS_CHESSSLOT_H

#include "ChessPiece.h"


// 格子
class ChessSlot {
private:
    ChessPiece *piece;

public:
    ChessSlot();

    ChessPiece *getPiece();

    void setPiece(ChessPiece *thePiece);
};


#endif //SUNNYCHESS_CHESSSLOT_H
