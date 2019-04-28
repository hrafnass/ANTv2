#ifndef CALCULATION_H
#define CALCULATION_H
#include<vector>
#include<algorithm>

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
    void calcValues(vector<int> reaction_times, int all_trials, int right_trials);
private:
    // functions for calculation of all values
    void calcAverageReactionTime(vector<int> reaction_times);   // calculates the average reaction time of all reaction times
    double calcMedian(vector<int> to_median);                   // calculates the median of an vector<int>
    void calcRightPercentage(int all_trials, int right_trials); // calculates the percentage of right reactions
    void calcEffects(vector<int> reaction_times1, vector<int>reaction_times2);
    // variables - calculated values
    double average;
    double median;
    double percentage;
    double effects;
};

#endif // CALCULATION_H
