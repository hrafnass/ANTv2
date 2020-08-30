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
    Calculation();

    void ResetCalculation();    // resets the calculation values
    void CalcValues();          // calculates the

private:
    // calculates the median
    float Median(std::vector<int>* arg_v);
    // fills the vectors with the needed reaction times - iterates one time over the run list
    void FillVectors(Run* arg_run);
    // calculates an effect
    float CalcEffect(vector<int>* arg_v1, vector<int>* arg_v2);

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
