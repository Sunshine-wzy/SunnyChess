#ifndef SUNNYCHESS_GOMOKUCHESSBOARD_H
#define SUNNYCHESS_GOMOKUCHESSBOARD_H

#include "ChessBoard.h"
#include "Direction.h"


// 五子棋棋盘
class GomokuChessBoard : public ChessBoard {
private:
    // 判定棋子数
    int judgeCount;
    
    
public:
    GomokuChessBoard(int x, int y, int width, int height, GomokuOptions &options);

    bool judge(int x, int y) override;

    void turnRound() override;
    
    // 检测direction方向的同色棋子数
    int judgeByDirection(int x, int y, Direction &direction);

    int getJudgeCount() const;

    void setJudgeCount(int judgeCount);

    void init(ChessOptions &options) override;

};


#endif //SUNNYCHESS_GOMOKUCHESSBOARD_H
