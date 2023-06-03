#include "GomokuChessBoard.h"
#include <set>
#include <cstdlib>

GomokuChessBoard::GomokuChessBoard(int x, int y, int width, int height, GomokuOptions &options)
            : ChessBoard(x, y, width, height, options), judgeCount(5 - 1) {
    int selectionBoxHalfWidth = (int) (getSlotWidth() / 2);
    int selectionBoxHalfHeight = (int) (getSlotHeight() / 2);
    
    if (options.mode == GomokuOptions::Mode::BOT) {
        // 人机对战
        ChessPiece *typeUser = nullptr, *typeBot = nullptr;
        
        if (options.type == ChessPiece::black) {
            // user先手
            typeUser = ChessPiece::black;
            typeBot = ChessPiece::white;
        } else if (options.type == ChessPiece::white) {
            // bot先手
            typeUser = ChessPiece::white;
            typeBot = ChessPiece::black;
        } else {
            // 随机先手
            if (std::rand() % 2 == 0) { // NOLINT(cert-msc50-cpp)
                typeUser = ChessPiece::black;
                typeBot = ChessPiece::white;
            } else {
                typeUser = ChessPiece::white;
                typeBot = ChessPiece::black;
            }
        }

        players.push_back(new User(typeUser, selectionBoxHalfWidth, selectionBoxHalfHeight, KeySettings {0x57, 0x53, 0x41, 0x44, 0x52}));
        players.push_back(new Bot(typeBot, selectionBoxHalfWidth, selectionBoxHalfHeight));
    } else if (options.mode == GomokuOptions::Mode::FRIEND) {
        // 好友对局
        if (options.number == 2) {
            // 双人对弈
            ChessPiece *typePlayer1 = nullptr, *typePlayer2 = nullptr;

            if (options.type == ChessPiece::black) {
                // player1先手
                typePlayer1 = ChessPiece::black;
                typePlayer2 = ChessPiece::white;
            } else if (options.type == ChessPiece::white) {
                // player2先手
                typePlayer1 = ChessPiece::white;
                typePlayer2 = ChessPiece::black;
            } else {
                // 随机先手
                if (std::rand() % 2 == 0) { // NOLINT(cert-msc50-cpp)
                    typePlayer1 = ChessPiece::black;
                    typePlayer2 = ChessPiece::white;
                } else {
                    typePlayer1 = ChessPiece::white;
                    typePlayer2 = ChessPiece::black;
                }
            }
            
            players.push_back(new User(typePlayer1, selectionBoxHalfWidth, selectionBoxHalfHeight, KeySettings {0x57, 0x53, 0x41, 0x44, 0x52}));
            players.push_back(new User(typePlayer2, selectionBoxHalfWidth, selectionBoxHalfHeight, KeySettings {VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, 0x4D}));
        } else {
            // 多人对弈
            
        }
        
        std::set<ChessPiece> usedPieces;
    }

//    for (int i = 0; i < options.number; i++) {
//        players.push_back(new Player());
//    }
    
}

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
