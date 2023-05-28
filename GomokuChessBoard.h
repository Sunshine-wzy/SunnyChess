#ifndef SUNNYCHESS_GOMOKUCHESSBOARD_H
#define SUNNYCHESS_GOMOKUCHESSBOARD_H

#include "ChessBoard.h"
#include "Direction.h"


class GomokuChessBoard : public ChessBoard {
private:
    int judgeCount;
    
    
public:
    GomokuChessBoard(int x, int y, int width, int height, GomokuOptions &options);

    bool judge(int x, int y) override;

    void turnRound() override;
    
    int judgeByDirection(int x, int y, Direction &direction);

    int getJudgeCount() const;

    void setJudgeCount(int judgeCount);

    void init(ChessOptions &options) override;

};


#endif //SUNNYCHESS_GOMOKUCHESSBOARD_H
