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
