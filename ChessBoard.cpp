#include "ChessBoard.h"

ChessBoard::ChessBoard(int x, int y, int width, int height) : startX(x), startY(y), width(width), height(height),
                                                              boardImage(IMAGE(height + 20, height + 20)),
                                                              drawingImage(IMAGE()) {
    drawBoard();
}

void ChessBoard::draw() {
    drawPieces();

    SetWorkingImage();
    putimage(startX, startY, &drawingImage, SRCPAINT);
}

void ChessBoard::drawBoard() {
    SetWorkingImage(&boardImage);

    loadimage(&boardImage, _T("../resources/chessboard.jpg"), 1600, 1600);

    setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 2);
    setlinecolor(BLACK);
    
    for (int x1 = startX, i = 0; i < 19; i++, x1 = startX + width * i / 18) {
        line(x1, startY, x1, startY + height);
    }
    
    for (int y1 = startY, j = 0; j < 19; j++, y1 = startY + height * j / 18) {
        line(startX, y1, startX + width, y1);
    }
    setfillcolor(BLACK);
solidcircle(startX+width*3/18,startY+height*3/18,POINT_SIZE);
solidcircle(startX+width*9/18,startY+height*3/18,POINT_SIZE);
solidcircle(startX+width*15/18,startY+height*3/18,POINT_SIZE);
solidcircle(startX+width*3/18,startY+height*9/18,POINT_SIZE);
solidcircle(startX+width*9/18,startY+height*9/18,POINT_SIZE);
solidcircle(startX+width*15/18,startY+height*9/18,POINT_SIZE);
solidcircle(startX+width*3/18,startY+height*15/18,POINT_SIZE);
solidcircle(startX+width*9/18,startY+height*15/18,POINT_SIZE);
solidcircle(startX+width*15/18,startY+height*15/18,POINT_SIZE);
}

void ChessBoard::drawPieces() {
    SetWorkingImage(&drawingImage);
    drawingImage = boardImage;
    for(int n=0;n<CHESSBOARD_SIZE;n++)
    {
    for(int m=0;m<CHESSBOARD_SIZE;m++)
       {
        ChessPiece piece = slots[n][m].getPiece();
        if(piece.getColor() != 0)
          {
             int x = startX + n * width / (CHESSBOARD_SIZE - 1);
    int y = startY + m * height / (CHESSBOARD_SIZE - 1);
    int radius = 8;
    piece.draw(x,y,radius);
          }
       }
    }
}

bool ChessBoard::getPosition(Position *position, int x, int y) {


    position = nullptr;
    return false;
}
