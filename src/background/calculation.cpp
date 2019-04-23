#include "calculation.h"

//set all vairables 0
Calculation::Calculation(){
    average = 0;
    percentage = 0;
    effects = 0;
    median = 0;
}

// all getter
double Calculation::getAverage(){
    return average;
}

double Calculation::getRightPercentage(){
    return percentage;
}

double Calculation::getEffects() {
    return effects;
}

double Calculation::getMedian(){
    return median;
}

// resetting all values
void Calculation::resetValues(){
    // set all calculated values to zero
    average = 0;
    percentage = 0;
    effects = 0;
    median = 0;
}

// calculate all values
void Calculation::calcValues(vector<int> reaction_times, int all_trials, int right_trials){
    calcAverageReactionTime(reaction_times);        // calculates the reaction times
    calcRightPercentage(all_trials, right_trials);  // calculates the percentage of right reactions
}

// all calculation functions
// average:
// calculation: (sum of all reaction times) / (number of reactio times)
void Calculation::calcAverageReactionTime(vector<int> reaction_times){
    vector<int>::iterator i;   // iterator over reaction_times
    int reaction_values = 0;    // saves the reaction_times values
    // iterates over all values in reaction_times
    for(i = reaction_times.begin(); i != reaction_times.end(); ++i){
        reaction_values = reaction_values + *i;
    }
    // calculates the average rection time and save it in average
    average = reaction_values / reaction_times.size();
}

// right percentage:
// calculation: ((number of right trials) / (number of all trials)) * 100
void Calculation::calcRightPercentage(int all_trials, int right_trials) {
    percentage = (right_trials/all_trials)*100;
}

// median:
/*
 * calculation:
 *  even: 1/2*(to_median.at(to_median.size()/2) + to_median.at(to_median.size()/2+1))
 *  odd: to_median.at((to_median.size()+1)/2)
 * */
double Calculation::calcMedian(vector<int> to_median){
    sort(to_median.begin(), to_median.end());       // sorting the to_median vector
    unsigned int size = to_median.size();           // saves the vector size
    if(size == 0)                                   // returns -1 if there is an error with to_median
        return -1;
    double median = 0;                              // saves the return value
    // check if the vector size is odd or even
    if(to_median.size() % 2){   // to_median.size % 2 = 1 -> size is odd
        unsigned int position = (size+1)/2;         // calculates the position in to_median
        median = to_median.at(position);
    }else{                      // to_median.size % 2 = 0 -> size is even
        median = (1/2)*(to_median.at(size/2)+ to_median.at(size/2+1));
    }
    return median;
}

/* calcEffects calculate the conflict/orientation/alertness effect
 * reaction_times1 is the first vector for the median calculation
 * reaction_times2 is the seconded vector for the median calculation */
void Calculation::calcEffects(vector<int> reaction_times1, vector<int>reaction_times2){
    effects = calcMedian(reaction_times1) - calcMedian(reaction_times2);  // calculates the effect value
}
