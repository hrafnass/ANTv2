#include "precisetimer.h"

PreciseTimer::PreciseTimer()
{
    QueryPerformanceFrequency(&frequency);  // cached the counter frequency
}

// public functions:

// sets time stamps
void PreciseTimer::setTimeStamp(bool start_or_stop){
    QueryPerformanceCounter(&stamp);
    if(start_or_stop)
        start = stamp;
    else
        stop = stamp;
}

// return elapsed time in micro seconds
long long PreciseTimer::elapsedTimeInMicroSecs(){
    LARGE_INTEGER elapsed_microssecs;
    elapsed_microssecs.QuadPart = start.QuadPart - stop.QuadPart;           // calcs the ticks difference
    elapsed_microssecs.QuadPart = elapsed_microssecs.QuadPart*MICROS_SECS;  // convert into microseconds
    elapsed_microssecs.QuadPart = elapsed_microssecs.QuadPart / frequency.QuadPart;    // calculate the elapsed time in microseconds
    return elapsed_microssecs.QuadPart;
}

// return time in mili seconds
long long PreciseTimer::elapsedTimeInMiliSecs(){
    LARGE_INTEGER elapsed_milisecs;
}


// private functions
// resets all stamps - used in time elapsing functions
void PreciseTimer::resetValues(){
    // set all stamps to a negativ value
    start.QuadPart = -1;
    stamp.QuadPart = -1;
    stop.QuadPart = -1;
}
