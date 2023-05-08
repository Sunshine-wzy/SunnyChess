#ifndef SUNNYCHESS_GOMOKUCHESSBOARD_H
#define SUNNYCHESS_GOMOKUCHESSBOARD_H

#include "ChessBoard.h"


class GomokuChessBoard : public ChessBoard {
    
    
public:
    GomokuChessBoard(int x, int y, int width, int height);

    bool judge(int x, int y) override;
};


#endif //SUNNYCHESS_GOMOKUCHESSBOARD_H
