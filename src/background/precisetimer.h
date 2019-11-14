#ifndef PRECISETIMER_H
#define PRECISETIMER_H

#include <windows.h>
#include <iostream>

using namespace std;

// constants to measure the time stamp
#define START true      // time stamp saved in start
#define STOP  false     // time stamp saved int stop

#define MILI_SECS 1000      // used in elapsedTimeInMiliSecs
#define MICROS_SECS 1000000 // used in elapsedTimeInMicroSecs

// check for the elapse functions return
#define ELAPSE_ERROR -1     // one time stamp isn't measured

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
 * long long elapsed_time;
 * timer.setTimeStamp(START);
 * sleep(...);
 * timer.setTimeStamp(STOP);
 * elapsed_time = timer.elapsedTimeIn...Secs()   // values in micro or mili seconds
 *
 */

class PreciseTimer
{
public:
    PreciseTimer();
    void setTimeStamp(bool);
    long long elapsedTimeInMicroSecs();     // calculates the elapsed time in microseconds
    long long elapsedTimeInMiliSecs();      //                      -"-       miliseconds
private:
    // functions:
    void resetValues();                     // reset all stamps to -1
    // calc the elapsed time and uses then resetValues
    void calcElapsedTime(long long, LARGE_INTEGER*);
    // saves the needed time stamps
    LARGE_INTEGER start;
    LARGE_INTEGER stop;
    // hold the frequency of the counter in the cache
    LARGE_INTEGER frequency;
    // stamp for setTimeStamp
    LARGE_INTEGER stamp;
};

#endif // PRECISETIMER_H
