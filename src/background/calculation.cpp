#include "calculation.h"

// public methods
void Calculation::ResetCalculation(){
    // reset calculations
    confict_effect = 0;
    orientation_effect = 0;
    alertnes_effect = 0;
    median_rt = 0;
    error_sum = 0;
    // reset vectors
    v_double_cue.clear();
    v_no_cue.clear();
    v_spatial_cue.clear();
    v_center_cue.clear();
    v_congruent.clear();
    v_incongruent.clear();
    v_rt.clear();
}


// private methods
// calculates the Median from a vector of reaction times
float Calculation::Median(std::vector<int>* arg_v){
    unsigned long long pos = arg_v->size()/2;   // calcs the postion
    // sort the vector ascending
    sort(arg_v->begin(), arg_v->end());
    // check if the vector size is even
    if((arg_v->size() % 2) != 0){    // vector is uneven
        return static_cast<float>(arg_v->at(pos));
    }
    return static_cast<float>((arg_v->at(pos-1) + arg_v->at(pos)) / 2); // the median with even vector size
}

// calculates an effect - differences of two medians
float Calculation::CalcEffect(vector<int> *arg_v1, vector<int> *arg_v2){
    return (Median(arg_v1) - Median(arg_v2));
}
