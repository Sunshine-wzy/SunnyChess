#ifndef SUNNYCHESS_CHESSOPTIONS_H
#define SUNNYCHESS_CHESSOPTIONS_H


enum class SelectChessType {
    random,
    black,
    white
};


class ChessOptions {
public:
    SelectChessType type;
    int size;
    
    
    ChessOptions();
    
};


class GomokuOptions : public ChessOptions {
private:
    
    
public:
    GomokuOptions();
    
};


#endif //SUNNYCHESS_CHESSOPTIONS_H
