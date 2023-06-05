#include "Timer.h"

Timer::Timer() : start(time(nullptr)), last(start) {}

time_t Timer::getTime() {
    last = time(nullptr);
    return last - start;
}

tm *Timer::getTm() {
    time_t theTime = getTime();
    return gmtime(&theTime);
}

void Timer::reset() {
    start = time(nullptr);
    last = start;
}

time_t Timer::getLastTime() const {
    return last - start;
}

tm *Timer::getLastTm() const {
    time_t theTime = getLastTime();
    return gmtime(&theTime);
}
