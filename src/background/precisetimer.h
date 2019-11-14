#ifndef PRECISETIMER_H
#define PRECISETIMER_H

#include <windows.h>
#include <iostream>

using namespace std;

// constants to measure the time stamp
#define START true      // time stamp saved in start
#define STOP  false     // time stamp saved int stop

// Measures with the windows api the time in ms accuracy.

class PreciseTimer
{
public:
    PreciseTimer();
    bool init();
    bool setTimeStamp(bool);
    long elapsed();         // calculates the differenz between start and stop and set them to 0
private:
    LARGE_INTEGER start;
    LARGE_INTEGER stop;
    LARGE_INTEGER frequency;
};

#endif // PRECISETIMER_H
