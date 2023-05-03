#ifndef SUNNYCHESS_CHESSBOARD_H
#define SUNNYCHESS_CHESSBOARD_H

#include "ChessSlot.h"

#define CHESSBOARD_SIZE 19

class Chessboard {
private:
    ChessSlot slots[CHESSBOARD_SIZE][CHESSBOARD_SIZE];
    
public:
    Chessboard();
    
};


#endif //SUNNYCHESS_CHESSBOARD_H
