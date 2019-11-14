#ifndef PRECISETIMER_H
#define PRECISETIMER_H

#include <windows.h>

// Measures with the windows api the time in ms accuracy.

class PreciseTimer
{
public:
    PreciseTimer();
    bool startTimer();      // start the timer
    bool stopTimer();       // stop the timer
    long elapsed();         // calculates the differenz between start and stop and set them to 0
private:
    /*
    TIME start;
    TIME stop;
    */
};

#endif // PRECISETIMER_H
