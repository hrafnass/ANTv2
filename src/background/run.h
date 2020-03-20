#ifndef RUN_H
#define RUN_H
#include <algorithm>
#include <random>       // std::default_random_engine
#include <iostream>

#include "trial.h"

using namespace std;

class Run{
public:
    Run();
    // TrialVector positions
    Trial NextTrial();
    vector<Trial>::iterator GetVectorEnd();
    vector<Trial>::iterator GetVectorStart();
    // measured values
    bool SetMeasuredValues(int reaction_time=-1, bool reaction=false);  // measure reaction time and reaction
    bool CleanMeasuredValues();     // delete measured values
private:
    bool CreateAndAddTrial(TrialComponents::ArrowCombinations arg_combi, TrialComponents::ArrowPositions arg_pos, TrialComponents::DirectionMidArrow arg_dir);
    bool FillTrialVector();         // fill a trial vector - iterates over the three components added as arguments in CreateAndAddTrial and runs this function
    bool ShuffelTrialVector();      // shuffel this vector

    // trial vector
    vector<Trial> v_trial;          // saves all trials
};

#endif // RUN_H
