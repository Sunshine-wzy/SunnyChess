#ifndef SUNNYCHESS_TIMER_H
#define SUNNYCHESS_TIMER_H

#include <ctime>


class Timer {
private:
    std::time_t start;
    std::time_t last;
    
public:
    Timer();
    
    time_t getTime();
    
    tm *getTm();
    
    void reset();

    time_t getLastTime() const;
    
    tm *getLastTm() const;

};


#endif //SUNNYCHESS_TIMER_H
