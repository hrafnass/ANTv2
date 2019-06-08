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
void Calculation::calcValues(Run *run){
    calcAverageReactionTime(run);        // calculates the reaction times
    calcRightPercentage(run->getVectorSize(), run->getNmbrAllRightReactions());  // calculates the percentage of right reactions
    calcMedian(run);        // calculates the median
}

// all calculation functions
// average without negativ values -> (no reactions):
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
    if(i == 0){
        average = -1;   // no values existing - everything is -1
        cout << "Error - No reaction value over -1 - no reaction measured"<<endl;
        return;
    }
    // calculates the average rection time and save it in average
    average = reaction_values / i;
}

// right percentage:
// calculation: ((number of right trials) / (number of all trials)) * 100
void Calculation::calcRightPercentage(int all_trials, int right_trials) {
    if(all_trials == 0){
        cout << "Error: No Trials founded!!!" << endl;
        percentage = -1;        // no values existing - everything is -1
        return;
    }
    cout << "right trials: " << right_trials << " all trials: " << all_trials << endl;
    percentage = (right_trials/all_trials)*100;
}

// median for reaction times:
/*
 * calculation:
 *  even: 1/2*(to_median.at(to_median.size()/2) + to_median.at(to_median.size()/2+1))
 *  odd: to_median.at((to_median.size()+1)/2)
 *  - includes all negative values (Trials with no reactions)
 * */
bool Calculation::calcMedian(Run *calc_median){
    sort(calc_median->getVectorStart(), calc_median->getVectorEnd(), compareTimeFunction); // sorting the to_median vector
    // calculates the vector positions
    unsigned int odd_pos = (calc_median->getVectorSize()+1)/2;
    unsigned int even_pos = (calc_median->getVectorSize())/2;

    // median calculation
    if(calc_median->getVectorSize()%2){ // 0 is in c/c++ false, everything else true -> odd vector size is true
        if(odd_pos < calc_median->getVectorSize()){ // position is from 0 to (vector size -1)
            median = calc_median->getTrialAtPos(odd_pos).getReactionTime(); // get the reaction time from the calculated trial
            cout << "median : " << median << " odd pos: " << odd_pos << endl;
            return true;
        }
    }else{                              // even
        // get the trial of the odd and the even median part
        if((even_pos+1) < calc_median->getVectorSize()){    // the median for a even vector size needs 2 values even_pos and even_pos +1
            // calculates the median
            median = 0.5*(calc_median->getTrialAtPos(even_pos).getReactionTime()+calc_median->getTrialAtPos(even_pos+1).getReactionTime());
            cout << "pos1: " << even_pos << " pos2: " << (even_pos+1) << " median: " << median << endl;
            return true;
        }
    }
    cout << "Error: Median couldn't calculated!!!" << endl;
    median = -1;        // the calculation got an error
    return false;
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
