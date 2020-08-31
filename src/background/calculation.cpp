#include "calculation.h"

// public methods
// Calculate all values from the measured values
bool Calculation::CalcValues(Run* arg_run){
    // no good run
    if(arg_run == nullptr)
        return false;
    // Fills all vectors and calculates the error sum
    if(!FillVectors(arg_run))
        return false;
    // calculates the effects
    confict_effect = CalcEffect(&v_congruent, &v_incongruent);
    orientation_effect = CalcEffect(&v_center_cue, &v_spatial_cue);
    alertnes_effect = CalcEffect(&v_no_cue, &v_double_cue);
    // calculates the median of the reaction time (all right reactions)
    median_rt = Median(&v_rt);
    return true;
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
// fills all vectors
bool Calculation::FillVectors(Run *arg_run){
    bool ok = false;    // param for GetTrial in arg_run
    Trial t;            // saves returned trial

    ResetVectors();     // clear all vectors
    error_sum = 0;      // error is calculated in FillVector

    // if run isn't filled
    if(arg_run == nullptr)
        return false;
    // iterate over the run
    do {
        t = arg_run->GetTrial(&ok); // get the actuell trial
        // if the reaction is false
        if(!t.GetReaction() || t.GetReactionTime() < 150 || t.GetReactionTime() > 2000){
            ++error_sum;
        } else {    // if the reaction is right
            // check the cues and fill them in the vectorss
            switch (t.GetCue()) {
            case TrialComponents::Cue::non_cue:
                v_no_cue.push_back(t.GetReactionTime());
                break;
            case TrialComponents::Cue::double_cue:
                v_double_cue.push_back(t.GetReactionTime());
                break;
            case TrialComponents::Cue::center_cue:
                v_center_cue.push_back(t.GetReactionTime());
                break;
            default:
                v_spatial_cue.push_back(t.GetReactionTime());   // combines spatial cue up and down its the default value
                break;
            }
            // check in-/congruents fills the in-/congruent vectors
            if(t.GetArrowCombinations() == TrialComponents::ArrowCombinations::congruent)
                v_congruent.push_back(t.GetReactionTime());
            else if(t.GetArrowCombinations() == TrialComponents::ArrowCombinations::incongruent)
                v_incongruent.push_back(t.GetReactionTime());
        }
    } while (arg_run->NextTrial() && ok);

    return true;
}
