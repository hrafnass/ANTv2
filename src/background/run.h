#ifndef RUN_H
#define RUN_H
#include <algorithm>
#include <random>       // std::default_random_engine
#include <iostream>

#include "trial.h"

#define SET_RUN_LENGTH -1   // sets the run length to vector size - input for SetRunLength(int arg_length)

using namespace std;

class Run{
public:
    Run();
    Run(unsigned int runs);  // adds the number of runs for v_trials
    // TrialVector positions
    bool NextTrial();           // iterates to the next trial; returns false if the end is reached
    // setter vor the iterator
    void SetIteratorToStart() { it_v_trial = v_trial.begin();} // iterator to start
    // measured values
    bool SetMeasuredValues(int arg_reaction_time=-1, bool arg_reaction=false, bool arg_pressed=false); // saves the measured values in the actuell trial
    bool CleanMeasuredValues();     // delete all measured values in the trial vector and shuffels it
    // Getter for the actuell Trial
    Trial GetTrial(bool *size);     // getter for actuell trial
    int GetPosition() {return (it_v_trial - v_trial.begin());}  // getter for the position of the actuell trial
    // Setter and Getter for the run length
    // The run_length how many Trials of the vector you can use for a game loop i.e. 12 for a test game or
    // all for a normal game. The Constructor sets run_length to the vector size
    void SetRunLength(int arg_length); // if the input is -1 or bigger then v_trial.size run_length is set to v_trial.size
    unsigned int GetRunLength() { return run_length;}
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
    // saves the run_length
    unsigned int run_length;
};

#endif // RUN_H
