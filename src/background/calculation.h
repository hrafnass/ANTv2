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
    Calculation(Run* arg_run);

private:

    // effect values
    // *median = media of reaction times (trials with special settings)
    int confict_effect;         // in-)congruent differences of medians*
    int orientation_effect;     // center/spatial cue differences of medians*
    int alertnes_effect;        // no/double cue differences of medians*

    // run - saves the run adress
    Run* run;
};

#endif // CALCULATION_H
