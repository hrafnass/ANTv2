#ifndef MEASUREMENT_H
#define MEASUREMENT_H
#include<vector>
#include "trial.h"

using namespace std;

// saves all measured values
class Measurement
{
public:
    // Measurement(); - use the standard constructor, else c++ get an error
    void addTrial(Trial trial); // add a value in trial_values
    void clearValues();         // removes all values of trial_values
    vector<Trial> getValues();  // returns the trial vector
private:
    vector<Trial> trial_values; // saves all measured trials
};

#endif // MEASUREMENT_H
