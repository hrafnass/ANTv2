#ifndef RUN_H
#define RUN_H
#include <algorithm>
#include <random>       // std::default_random_engine
#include <iostream>

#include "trial.h"

using namespace std;

class Run{
public:
    Run(unsigned int runs);  // adds the number of runs for v_trials
    // TrialVector positions
    bool NextTrial();           // iterates to the next trial; returns false if the end is reached
    // measured values
    bool SetMeasuredValues(int arg_reaction_time=-1, bool arg_reaction=false); // saves the measured values in the actuell trial
    bool CleanMeasuredValues();     // delete all measured values in the trial vector and shuffels it
    // Getter for the actuell Trial
    Trial GetTrial(bool *size);
private:
    // fill the vector with trials
    bool CreateAndAddTrial(TrialComponents::ArrowCombinations arg_combi, TrialComponents::ArrowPositions arg_pos, TrialComponents::DirectionMidArrow arg_dir);
    bool AddRuns(unsigned int arg_add);  // adds the number of Runs (saved in arg_add) to v_trial
    bool FillTrialVector();         // fill a trial vector - iterates over the three components added as arguments in CreateAndAddTrial and runs this function
    // shuffel this vector
    void ShuffelTrialVector() { shuffle(v_trial.begin(), v_trial.end(), generator);}

    // trial vector
    vector<Trial> v_trial;              // saves all trials
    vector<Trial>::iterator it_v_trial; // to iterate over all trials in vector
    // shuffeling
    random_device rd;  // the generator values aren't reproducable
    mt19937 generator; // random_generator for shuffelRun
};

#endif // RUN_H
