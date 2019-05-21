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

    // getter for all needed values
    double getAverage();                // average of all reaction times
    double getMedian();                 // median of all reaction times
    double getRightPercentage();        // percentage of all right decisions
    double getEffects();
    // resets all calculated values
    void resetValues();
    // calculates all values - run all private calculation functions
    void calcValues(vector<Run> reaction_times, int all_trials, int right_trials);
private:
    // functions for calculation of all values
    void calcAverageReactionTime(Run *reaction_times);      // calculates the average reaction time of all reaction times, which aren't -1 (no reaction, trials after game quit)
    double calcMedian(Run *median);                         // calculates the median of an vector<int>
    void calcRightPercentage(int all_trials, int right_trials); // calculates the percentage of right reactions
    void calcEffects(vector<Run> reaction_times1, vector<Run>reaction_times2);
    bool compareTimeFunction(Trial& t1, Trial &t2); // a function for sort all Trials in run vector (compare all time values)

    // variables - calculated values
    double average;
    double median;
    double percentage;
    double effects;
};

#endif // CALCULATION_H
