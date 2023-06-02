#include "GomokuChessBoard.h"

GomokuChessBoard::GomokuChessBoard(int x, int y, int width, int height, GomokuOptions &options)
            : ChessBoard(x, y, width, height, options), judgeCount(5 - 1) {}

bool GomokuChessBoard::judge(int x, int y) {
    if (judgeByDirection(x, y, Direction::right) + judgeByDirection(x, y, Direction::left) >= judgeCount)
        return true;

    if (judgeByDirection(x, y, Direction::up) + judgeByDirection(x, y, Direction::down) >= judgeCount)
        return true;

    if (judgeByDirection(x, y, Direction::upRight) + judgeByDirection(x, y, Direction::downLeft) >= judgeCount)
        return true;

    if (judgeByDirection(x, y, Direction::upLeft) + judgeByDirection(x, y, Direction::downRight) >= judgeCount)
        return true;

    return false;
}

void GomokuChessBoard::turnRound() {
    ++getRound();
    
    if (getRound() == players.end()) {
        setRound(players.begin());
    }
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

int GomokuChessBoard::judgeByDirection(int x, int y, Direction &direction) {
    x += direction.getOffsetX();
    y += direction.getOffsetY();

    if (isOrderInBoard(x, y) && slots[x][y].getPiece() == getRoundPlayer()->getPiece()) {
        return judgeByDirection(x, y, direction) + 1;
    }

    return 0;
}

#pragma clang diagnostic pop

int GomokuChessBoard::getJudgeCount() const {
    return judgeCount;
}

void GomokuChessBoard::setJudgeCount(int count) {
    judgeCount = count;
}

void GomokuChessBoard::init(ChessOptions &options) {
    ChessBoard::init(options);
    
    auto gomokuOptions = dynamic_cast<GomokuOptions &>(options);
    
}
