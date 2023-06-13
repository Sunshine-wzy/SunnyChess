#ifndef SUNNYCHESS_TIMER_H
#define SUNNYCHESS_TIMER_H

#include <ctime>


class Timer {
private:
    std::time_t start;          // 开始时间
    std::time_t last;           // 上一次更新时间
    
public:
    Timer();
    
    // 获取从开始到现在所经过的时间
    time_t getTime();

    // 获取从开始到现在所经过的时间
    tm *getTm();
    
    // 重置开始时间（设置为当前时间）
    void reset();

    // 获取上一次更新时间
    time_t getLastTime() const;

    // 获取上一次更新时间
    tm *getLastTm() const;

};


#endif //SUNNYCHESS_TIMER_H
