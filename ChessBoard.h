#ifndef SUNNYCHESS_CHESSBOARD_H
#define SUNNYCHESS_CHESSBOARD_H

#include "ChessSlot.h"
#include "Position.h"
#include "ChessOptions.h"
#include "Player.h"
#include <vector>
#include <list>
#include <string>


// 棋盘
class ChessBoard {
protected:
    // 格子
    std::vector< std::vector<ChessSlot> > slots;
    // 所有玩家
    std::vector<Player *> players;
    // 落子记录（用于悔棋）
    std::list< std::pair<ChessPiece *, Position> > records;
    
private:
    int startX;             // 左上角x坐标
    int startY;             // 左上角y坐标
    int baseX;              // 格子左上角基础x坐标（相对于startX的偏移量）
    int baseY;              // 格子左上角基础y坐标（相对于startY的偏移量）
    int width;              // 宽
    int height;             // 高
    int extraWidth;         // 额外宽
    int extraHeight;        // 额外高

    int size;               // 行列数

    double slotWidth;       // 格子宽
    double slotHeight;      // 格子高
    int totalWidth;         // 总共宽
    int totalHeight;        // 总共高
    
    int pieceRadius;        // 棋子半径

    IMAGE boardImage;       // 棋盘背景以及基础格子
    IMAGE drawingImage;     // 包括棋子的棋盘

    // 当前回合玩家
    std::vector<Player *>::iterator round;
    // 玩家数量
    int number;
    
    // 禁止图片
    IMAGE imageForbidden;

public:
    ChessBoard(int x, int y, int width, int height, ChessOptions &options);
    
    virtual ~ChessBoard();

    // 画出整个棋盘（基础格子+棋子）
    void draw();

    // 画出棋盘的基础格子
    void drawBoard();

    // 画出棋子
    void drawPieces();

    // 根据坐标(x, y)获取格子中心点坐标
    // 若(x, y)不在任何一个格子内，则返回false
    bool getCenterPositionByPosition(Position &position, int x, int y) const;

    // 根据坐标(x, y)获取格子序号
    bool getOrderByPosition(Position &order, int x, int y) const;

    // 根据序号(x, y)获取格子中心点坐标
    bool getCenterPositionByOrder(Position &position, int x, int y) const;

    // 序号(x, y)是否在棋盘内
    bool isOrderInBoard(int x, int y) const;

    // 坐标(x, y)是否在棋盘内
    bool isPositionInBoard(int x, int y) const;


    // 初始化棋盘
    virtual void init(ChessOptions &options);

    // 尝试向序号(x, y)放置棋子
    virtual bool placePiece(ChessPiece *piece, int x, int y);

    virtual bool placePiece(ChessPiece *piece, Position &order);
    
    // 尝试向序号(x, y)放置当前回合玩家的棋子
    virtual bool placePiece(int x, int y);
    
    virtual bool placePiece(Position &order);

    // 胜利判定 落子时触发
    virtual bool judge(int x, int y) = 0;
    
    // 记录一次落子
    virtual void record(ChessPiece *piece, int x, int y);
    
    virtual void record(int x, int y);
    
    // 悔棋
    virtual void retract();
    
    
    // 获取当前回合玩家的迭代器
    typename std::vector<Player *>::iterator &getRound();

    // 设置当前回合玩家的迭代器
    void setRound(typename std::vector<Player *>::iterator theRound);
    
    // 获取当前回合玩家
    Player *getRoundPlayer();
    
    // 回合更替
    virtual void turnRound() = 0;

    int getStartX() const;

    int getStartY() const;

    int getBaseX() const;

    int getBaseY() const;

    int getWidth() const;

    int getHeight() const;

    int getExtraWidth() const;

    int getExtraHeight() const;

    int getSize() const;

    double getSlotWidth() const;

    double getSlotHeight() const;

    int getTotalWidth() const;

    int getTotalHeight() const;

    int getNumber() const;

    IMAGE &getImageForbidden();
    
    // 设置(x, y)处格子的棋子类型
    void setPiece(ChessPiece *piece, int x, int y);
    
    void setPiece(ChessPiece *piece, const Position &position);
    
    // 获取(x, y)处格子的棋子类型
    ChessPiece *getPiece(int x, int y);


    // 点大小
    static const int POINT_SIZE = 6;
};


#endif //SUNNYCHESS_CHESSBOARD_H
