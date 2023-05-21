#include "GomokuChessBoard.h"

GomokuChessBoard::GomokuChessBoard(int x, int y, int width, int height, int size) : ChessBoard(x, y, width, height, size), judgeCount(5 - 1) {
    
}

bool GomokuChessBoard::judge(int x, int y) {
    if (judgeByDirection(x, y, Direction::right) + judgeByDirection(x, y, Direction::left) >= judgeCount)
        return true;
    
    if (judgeByDirection(x, y, Direction::up) + judgeByDirection(x, y, Direction::down) >= judgeCount)
        return true;
    
    if (judgeByDirection(x, y, Direction::up_right) + judgeByDirection(x, y, Direction::down_left) >= judgeCount)
        return true;
    
    if (judgeByDirection(x, y, Direction::up_left) + judgeByDirection(x, y, Direction::down_right) >= judgeCount)
        return true;
    
    return false;
}

void GomokuChessBoard::turnRound() {
    if (getRound() == ChessPiece::black) {
        setRound(ChessPiece::white);
    } else if (getRound() == ChessPiece::white) {
        setRound(ChessPiece::black);
    }
}

int GomokuChessBoard::judgeByDirection(int x, int y, Direction &direction) {
    x += direction.getOffsetX();
    y += direction.getOffsetY();
    
    if (isOrderInBoard(x, y) && slots[x][y].getPiece() == getRound()) {
        return judgeByDirection(x, y, direction) + 1;
    }
    
    return 0;
}

int GomokuChessBoard::getJudgeCount() const {
    return judgeCount;
}

void GomokuChessBoard::setJudgeCount(int count) {
    judgeCount = count;
}
