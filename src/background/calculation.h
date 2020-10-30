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

#ifndef CALCULATION_H
#define CALCULATION_H
#include<vector>
#include<algorithm>

#include "run.h"

using namespace std;

// calculates everything every needed value from the measured values
class Calculation
{
public:
    void Reset();                           // resets the whole calculation
    bool ReCalc(Run* arg_run);              // clears all variables and delete all init values
    bool CalcValues(Run* arg_run);          // calculates the

    // getter effects
    float GetConflict() { return confict_effect;}
    float GetOrientation() { return orientation_effect;}
    float GetAlertness() { return alertnes_effect;}
    // getter median and error values
    float GetRtMedian(){ return median_rt;}
    unsigned int GetErrorSum() { return error_sum;}

private:
    void ResetCalculation();    // resets the calculation values
    void ResetVectors();        // clears all vectors
    // calculates the median
    float Median(std::vector<int>* arg_v);
    // fills the vectors with the needed reaction times - iterates one time over the run list
    bool FillVectors(Run* arg_run);
    // calculates an effect
    float CalcEffect(vector<int>* arg_v1, vector<int>* arg_v2);

    // RESEARCH VALUES
    unsigned int error_sum;     	// number of all trials with Trial.Reaction == false
    float median_rt;                // saves the median of the reaction time
    // effect values
    // median = media of reaction times (trials with special settings)
    float confict_effect;           // in-)congruent differences of medians*
    float orientation_effect;       // center/spatial cue differences of medians*
    float alertnes_effect;          // no/double cue differences of medians*  
    // saves the vectors for reaction times
    // (right reactions Trial.Reaction == true & 150ms < reaction time <= 2000ms)
    // alertness vectors
    vector<int> v_double_cue;
    vector<int> v_no_cue;
    // orientation vectors
    vector<int> v_center_cue;
    vector<int> v_spatial_cue;
    // vectors for in/congruent trials
    vector<int> v_congruent;
    vector<int> v_incongruent;
    // vector for all right reactions
    vector<int> v_rt;
};


#endif // CALCULATION_H
