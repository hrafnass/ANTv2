#include "calculation.h"

// public methods
// Calculate all values from the measured values
void Calculation::CalcValues(){
    // calculates the effects
    confict_effect = CalcEffect(&v_congruent, &v_incongruent);
    orientation_effect = CalcEffect(&v_center_cue, &v_spatial_cue);
    alertnes_effect = CalcEffect(&v_no_cue, &v_double_cue);
    // calculates the median of the reaction time (all right reactions)
    median_rt = Median(&v_rt);
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

// reset all vectors
void Calculation::ResetVectors(){
    // reset vectors
    v_double_cue.clear();
    v_no_cue.clear();
    v_spatial_cue.clear();
    v_center_cue.clear();
    v_congruent.clear();
    v_incongruent.clear();
    v_rt.clear();
}
// reset the calculation
void Calculation::ResetCalculation(){
    // reset calculations
    confict_effect = 0;
    orientation_effect = 0;
    alertnes_effect = 0;
    median_rt = 0;
    error_sum = 0;
}

// calculates an effect - differences of two medians
float Calculation::CalcEffect(vector<int> *arg_v1, vector<int> *arg_v2){
    return (Median(arg_v1) - Median(arg_v2));
}
