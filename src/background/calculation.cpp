/* ANTv2
 * Copyright (C) 2020 Siegfried Gauggel
 * Copyright (C) 2020 Marcel Gräfenstein
 * 
 * This file is part of ANTv2.
 * 
 * ANTv2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * ANTv2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with ANTv2.  If not, see <https://www.gnu.org/licenses/>.
 */


#include "calculation.h"

// public methods
// Calculate all values from the measured values
bool Calculation::CalcValues(Run* arg_run){
    cout << "[*] CalcValues - Calculation"<<endl;
    // no good run
    if(arg_run == nullptr){
        cout << "[***] Error - CalcValues: run = nullptr!" << endl;
        return false;
    }
    // Fills all vectors and calculates the error sum
    if(!FillVectors(arg_run)){
        cout << "[***] Error - FillVectors doesn't successed!" << endl;
        return false;
    }
    // calculates the effects
    confict_effect = CalcEffect(&v_congruent, &v_incongruent);
    orientation_effect = CalcEffect(&v_center_cue, &v_spatial_cue);
    alertnes_effect = CalcEffect(&v_no_cue, &v_double_cue);
    // calculates the median of the reaction time (all right reactions)
    median_rt = Median(&v_rt);
    return true;
}

// Recalculates the Values
bool Calculation::ReCalc(Run *arg_run){
    cout << "[*] ReCalc - Calculation"<<endl;
    Reset();    // resets vectors and calculated values
    if(!CalcValues(arg_run))    // if the calculation was false
        return false;
    return true;
}

// Resets all values
void Calculation::Reset(){
    cout << "[*] Reset - Calculation"<<endl;
    // deletes/inits all needed values - can be calculated new over ReCalc or CalcValues
    ResetCalculation();
    ResetVectors();
}


// private methods
// calculates the Median from a vector of reaction times
float Calculation::Median(std::vector<int>* arg_v){
    cout << "[*] Median - Calculation"<<endl;
    // check if the vector has a any elements
    if(arg_v->size() == 0)  // if the vector has no elements the median is zero
        return 0.0;
    unsigned long long pos = arg_v->size()/2;   // calcs the postion
    // sort the vector ascending
    sort(arg_v->begin(), arg_v->end());
    // check if the vector size is even
    if((arg_v->size() % 2) != 0){    // vector is uneven
        return static_cast<float>(arg_v->at(pos));
    }
    int sum = arg_v->at(pos-1) + arg_v->at(pos);  // the 2 mid values of the set
    float ret = static_cast<float>(sum) / 2.0;    // calc the median
    return ret;
}
// reset all vectors
void Calculation::ResetVectors(){
    cout << "[*] ResetVectors - Calculation"<<endl;
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
    cout << "[*] ResetCalculation - Calculation"<<endl;
    // reset calculations
    confict_effect = 0;
    orientation_effect = 0;
    alertnes_effect = 0;
    median_rt = 0;
    error_sum = 0;
}
// calculates an effect - differences of two medians
float Calculation::CalcEffect(vector<int> *arg_v1, vector<int> *arg_v2){
    cout << "[*] CalcEffect"<<endl;
    return (Median(arg_v1) - Median(arg_v2));
}
// fills all vectors
bool Calculation::FillVectors(Run *arg_run){
    cout << "[*] FillVectors - Calculation"<<endl;
    bool ok = false;    // param for GetTrial in arg_run
    Trial t;            // saves returned trial

    ResetVectors();     // clear all vectors
    error_sum = 0;      // error is calculated in FillVector

    // if run isn't filled
    if(arg_run == nullptr){
        cout << "[***] Error FillVectors - arg_run == nulptr"<<endl;
        return false;
    }

    arg_run->RTFilter(150,2000);    // everything what is lower then 150ms or higher then 2000 ms is not used for calculations

    // iterate over the run
    do {
        t = arg_run->GetTrial(&ok); // get the actuell trial
        // if the reaction is false
        if(!t.GetReaction()){
            ++error_sum;
        } else {    // if the reaction is right
            // save all right reactions - max. 180 Trials
            if(v_rt.size() < 180)
                v_rt.push_back(t.GetReactionTime());
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

    cout << "[*] FillVectors - Calculation quit"<<endl;
    return true;
}
