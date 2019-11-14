#ifndef PRECISETIMER_H
#define PRECISETIMER_H

#include <windows.h>
#include <iostream>

using namespace std;

// constants to measure the time stamp
#define START true      // time stamp saved in start
#define STOP  false     // time stamp saved int stop

// Measures with the windows api the time in ms accuracy.
/*
 * Information about PreciseTimer:
 *
 * PreciseTimer uses the QueryPerfomanceCounter (QPC) of the Windows API.
 * The class only can used on Windows XP and higher without doubt.
 * On lower windows versions it could be that QPC doesn't work.
 *
 * Use:
 *
 * PreciseTimer timer;
 * timer.setTimeStamp(START);
 * sleep(...);
 * timer.setTimeStamp(STOP);
 * elapsed_time = timer.elapsed()   // values in ms
 *
 */

class PreciseTimer
{
public:
    PreciseTimer();
    // bool init();
    void setTimeStamp(bool);
    long elapsed();         // calculates the differenz between start and stop and reset the stamps
private:
    // saves the needed time stamps
    LARGE_INTEGER start;
    LARGE_INTEGER stop;
    // hold the frequency of the counter in the cache
    LARGE_INTEGER frequency;
    // stamp for setTimeStamp
    LARGE_INTEGER stamp;
};

#endif // PRECISETIMER_H
