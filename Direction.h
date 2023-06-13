#ifndef SUNNYCHESS_DIRECTION_H
#define SUNNYCHESS_DIRECTION_H


class Direction {
private:
    int offsetX;            // x偏移量
    int offsetY;            // y偏移量
    
public:
    Direction(int offsetX, int offsetY);

    int getOffsetX() const;

    int getOffsetY() const;


    static Direction right;
    static Direction left;
    static Direction up;
    static Direction down;
    static Direction upRight;
    static Direction downLeft;
    static Direction upLeft;
    static Direction downRight;
};


#endif //SUNNYCHESS_DIRECTION_H
