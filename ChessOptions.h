#ifndef SUNNYCHESS_CHESSOPTIONS_H
#define SUNNYCHESS_CHESSOPTIONS_H

#include "ChessPiece.h"


class ChessOptions {
public:
    ChessPiece *type;
    int size;
    int number;
    
    
    ChessOptions();
    
    virtual ~ChessOptions();
    
};


class GomokuOptions : public ChessOptions {
private:
    
    
public:
    GomokuOptions();
    
};


#endif //SUNNYCHESS_CHESSOPTIONS_H
