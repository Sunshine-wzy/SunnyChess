#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"

#include "GomokuChessBoard.h"
#include <list>
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

        User *user = new User(typeUser, selectionBoxHalfWidth, selectionBoxHalfHeight, *KeySettings::defaultSettings[1]);
        players.push_back(user);
        
        Bot *bot = new Bot(typeBot, *user, selectionBoxHalfWidth, selectionBoxHalfHeight);
        for (int i = 0; i <= getSize(); i++) {
            std::vector<int> row;
            for (int j = 0; j <= getSize(); j++) {
                row.push_back(0);
            }
            
            bot->scoreMap.push_back(row);
        }
        
        players.push_back(bot);
    } else if (options.mode == GomokuOptions::Mode::FRIEND) {
        // 好友对战
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
                if (std::rand() % 2 == 0) {
                    typePlayer1 = ChessPiece::black;
                    typePlayer2 = ChessPiece::white;
                } else {
                    typePlayer1 = ChessPiece::white;
                    typePlayer2 = ChessPiece::black;
                }
            }
            
            players.push_back(new User(typePlayer1, selectionBoxHalfWidth, selectionBoxHalfHeight, KeySettings::wsadq));
            players.push_back(new User(typePlayer2, selectionBoxHalfWidth, selectionBoxHalfHeight, KeySettings::udlrm));
        } else {
            // 多人对弈
            players.resize(options.number, nullptr);
            
            // 选择黑棋
            int blackNumber = std::rand() % options.number;
            players[blackNumber] = new User(ChessPiece::black, selectionBoxHalfWidth, selectionBoxHalfHeight, *KeySettings::defaultSettings[blackNumber + 1]);
            
            // 选择白棋
            int whiteNumber = std::rand() % (options.number - 1);
            if (whiteNumber >= blackNumber) whiteNumber++;
            players[whiteNumber] = new User(ChessPiece::white, selectionBoxHalfWidth, selectionBoxHalfHeight, *KeySettings::defaultSettings[whiteNumber + 1]);
            
            // 选择其他颜色棋
            std::list<ChessPiece *> unusedPieces = {ChessPiece::red, ChessPiece::yellow, ChessPiece::blue, ChessPiece::green};
            int currentNumber = 0;
            while (currentNumber < options.number) {
                if (currentNumber == blackNumber || currentNumber == whiteNumber) {
                    currentNumber++;
                    continue;
                }
                
                auto iter = unusedPieces.begin();
                int randomNumber = std::rand() % (int) unusedPieces.size();
                for (int i = 0; i < randomNumber; i++) {
                    ++iter;
                }
                
                ChessPiece *randomPiece = *iter;
                unusedPieces.erase(iter);
                players[currentNumber] = new User(randomPiece, selectionBoxHalfWidth, selectionBoxHalfHeight, *KeySettings::defaultSettings[currentNumber + 1]);
                
                currentNumber++;
            }
        }
    }
    
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

#pragma clang diagnostic pop