#include "calculation.h"

// init all needed and calculated values
Calculation::Calculation(Run* arg_run){
    run = arg_run;
    confict_effect = 0;
    orientation_effect = 0;
    alertnes_effect = 0;
}



// private methods

// calculates the Median from a vector of reaction times
float Median(std::vector<int>* arg_v){
    unsigned long long pos = arg_v->size()/2;   // calcs the postion
    // sort the vector ascending
    sort(arg_v->begin(), arg_v->end());
    // check if the vector size is even
    if((arg_v->size() % 2) != 0){    // vector is uneven
        return static_cast<float>(arg_v->at(pos));
    }
    return static_cast<float>((arg_v->at(pos-1) + arg_v->at(pos)) / 2); // the median with even vector size
}
