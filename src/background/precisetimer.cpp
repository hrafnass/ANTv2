#include "precisetimer.h"

PreciseTimer::PreciseTimer()
{

}

bool PreciseTimer::init(){
    // in windows xp and later it shouldn't happens
    if(!QueryPerformanceFrequency(&frequency)){
        cout << "Error: Hardware doesn't support high performance" << endl;
        return false;
    }

    /*if(frequency == 0){
        cout << "Error: Hardware doesn't support high performance" << endl;
        return false;
    }*/

    return true;
}
