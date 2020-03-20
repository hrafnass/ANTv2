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
    // fill the vector with trials
    bool CreateAndAddTrial(TrialComponents::ArrowCombinations arg_combi, TrialComponents::ArrowPositions arg_pos, TrialComponents::DirectionMidArrow arg_dir);
    bool FillTrialVector();         // fill a trial vector - iterates over the three components added as arguments in CreateAndAddTrial and runs this function
    // shuffel this vector
    void ShuffelTrialVector() { shuffle(v_trial.begin(), v_trial.end(), generator);}

    // trial vector
    vector<Trial> v_trial;          // saves all trials

    // shuffeling
    random_device rd;  // the generator values aren't reproducable
    mt19937 generator; // random_generator for shuffelRun
};

#endif // RUN_H
