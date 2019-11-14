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
    calcElapsedTime(MICROS_SECS, &elapsed_microssecs);
    return elapsed_microssecs.QuadPart;
}

// return time in mili seconds
long long PreciseTimer::elapsedTimeInMiliSecs(){
    LARGE_INTEGER elapsed_milisecs;
    calcElapsedTime(MILI_SECS, &elapsed_milisecs);
    return elapsed_milisecs.QuadPart;
}


// private functions:
// resets all stamps - used in time elapsing functions
void PreciseTimer::resetValues(){
    // set all stamps to a negativ value
    start.QuadPart = -1;
    stamp.QuadPart = -1;
    stop.QuadPart = -1;
}

// calculates the elapsed time
void PreciseTimer::calcElapsedTime(long long micro_or_mili, LARGE_INTEGER* elapsed){
    if(start.QuadPart == -1 || stop.QuadPart == -1){
        cout << "[*] Error: Time stamp isn't measured!!! " << endl;
        elapsed->QuadPart = ELAPSE_ERROR;
        return;
    }
    elapsed->QuadPart = start.QuadPart - stop.QuadPart;               // calcs the ticks difference
    elapsed->QuadPart = elapsed->QuadPart*micro_or_mili;    // convert into microseconds
    elapsed->QuadPart = elapsed->QuadPart / frequency.QuadPart;    // calculate the elapsed time in microseconds
    resetValues();  // resets the stamps
}
