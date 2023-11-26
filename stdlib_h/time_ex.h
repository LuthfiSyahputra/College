#ifndef TIME_EXTENDED_H
#define TIME_EXTENDED_H

#include <time.h>

// TIME
clock_t __globalLastClock = 0;
clock_t _startclock = 0;
time_t __globalTestTime = 0;
time_t* __globalTestTimeptr = &__globalTestTime;

#define SET_TESTCLK (_startclock = clock())
#define GET_TESTCLK (clock() - _startclock)

#define ELAPSED_CLK(lastclock) (clock() - lastclock)

clock_t _clockElapsed(void);
clock_t clockUpdateElapsed(register clock_t* _lastclock);
time_t* timeptr(void);
#define CUR_TIME localtime(timeptr())

// return clock since this function last call
clock_t _clockElapsed(void) {
    register clock_t lastclock = __globalLastClock;
    return ((__globalLastClock = clock()) - lastclock); 
}

// return clock elapsed since _lastclock and update _lastclock
clock_t clockUpdateElapsed(register clock_t* _lastclock) {
    register clock_t tempClock = *_lastclock;
    return ((*_lastclock = clock()) - tempClock); 
}

// time() but return the pointer to the global current time
time_t* timeptr(void) {
    time(__globalTestTimeptr); 
    return __globalTestTimeptr;
}




#endif