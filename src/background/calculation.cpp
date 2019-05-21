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
/* va
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
*/
// calculate all values
/*void Calculation::calcValues(vector<Run> reaction_times, int all_trials, int right_trials){
    calcAverageReactionTime(reaction_times);        // calculates the reaction times
    calcRightPercentage(all_trials, right_trials);  // calculates the percentage of right reactions
}*/

// all calculation functions
// average:
// calculation: (sum of all measured reaction times) / (number of the measured reaction times)
void Calculation::calcAverageReactionTime(Run *reaction_times){
    reaction_times->setIteratorToStart(); // set the iterator to start
    int reaction_values = 0;    // saves the reaction_times values
    int i = 0;                  // saves the number of counted values
    // iterates over all values in reaction_times
    while(reaction_times->readRun()){
        if(reaction_times->getActuellTrial().getReactionTime() > -1){
            reaction_values = reaction_values + reaction_times->getActuellTrial().getReactionTime(); // calculates the reaction time
            ++i;
        }
    }
    // calculates the average rection time and save it in average
    average = reaction_values / i;
}

// right percentage:
// calculation: ((number of right trials) / (number of all trials)) * 100
/*void Calculation::calcRightPercentage(int all_trials, int right_trials) {
    percentage = (right_trials/all_trials)*100;
}*/

// median for reaction times:
/*
 * calculation:
 *  even: 1/2*(to_median.at(to_median.size()/2) + to_median.at(to_median.size()/2+1))
 *  odd: to_median.at((to_median.size()+1)/2)
 *  - includes all negative values (Trials with no reactions)
 * */
double Calculation::calcMedian(Run *calc_median){
    sort(calc_median->getVectorStart(), calc_median->getVectorEnd(), compareTimeFunction);       // sorting the to_median vector
    double median = 0;                              // saves the return value
    // check if the vector size is odd or even
    if(calc_median->getVectorSize() % 2){           // to_median.size % 2 = 1 -> size is odd
        unsigned int position = (calc_median+1)/2;         // calculates the position in to_median
        median = to_median.at(position);
    }else{                      // to_median.size % 2 = 0 -> size is even
        median = (1/2)*(to_median.at(size/2)+ to_median.at(size/2+1));
    }
    return median;
}

// compare function for the sort algorithmus in calcMedian
bool Calculation::compareTimeFunction(Trial t1, Trial t2){
    return t1.getReactionTime() < t2.getReactionTime();
}

/* calcEffects calculate the conflict/orientation/alertness effect
 * reaction_times1 is the first vector for the median calculation
 * reaction_times2 is the seconded vector for the median calculation */
/*void Calculation::calcEffects(vector<Run> reaction_times1, vector<Run>reaction_times2){
    effects = calcMedian(reaction_times1) - calcMedian(reaction_times2);  // calculates the effect value
}*/
