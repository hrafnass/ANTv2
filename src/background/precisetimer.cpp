#include "precisetimer.h"

PreciseTimer::PreciseTimer()
{
    QueryPerformanceFrequency(&frequency);  // cached the counter frequency
}

/*bool PreciseTimer::init(){
    // in windows xp and later it shouldn't happens
    if(!QueryPerformanceFrequency(&frequency)){
        cout << "Error: Hardware doesn't support high performance" << endl;
        return false;
    }
    return true;
}*/

void PreciseTimer::setTimeStamp(bool start_or_stop){
    QueryPerformanceCounter(&stamp);
    if(start_or_stop)
        start = stamp;
    else
        stop = stamp;
}

long long PreciseTimer::elapsedTimeInMicroSecs(){
    LARGE_INTEGER elapsed_microssecs;
    elapsed_microssecs.QuadPart = start.QuadPart - stop.QuadPart;           // calcs the ticks difference
    elapsed_microssecs.QuadPart = elapsed_microssecs.QuadPart*MICROS_SECS;  // convert into microseconds
    elapsed_microssecs.QuadPart = elapsedTimeInMicroSecs() / frequency.QuadPart;    // calculate the elapsed time in microseconds
    return elapsed_microssecs.QuadPart;
}
