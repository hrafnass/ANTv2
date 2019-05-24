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
    cout << "Average Reactiontime" <<endl;
    calcAverageReactionTime(run);        // calculates the reaction times
    //cout << "right percentage"<<endl;
    calcRightPercentage(run->getVectorSize(), run->getNmbrAllRightReactions());  // calculates the percentage of right reactions
    cout << "calcmedian"<<endl;
    median = calcMedian(run);        // calculates the median
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
    cout << "reaction values sum: "<< reaction_values << "number of values: " << i <<endl;
    // calculates the average rection time and save it in average
    average = reaction_values / i;
}

// right percentage:
// calculation: ((number of right trials) / (number of all trials)) * 100
void Calculation::calcRightPercentage(int all_trials, int right_trials) { percentage = (right_trials/all_trials)*100;}

// median for reaction times:
/*
 * calculation:
 *  even: 1/2*(to_median.at(to_median.size()/2) + to_median.at(to_median.size()/2+1))
 *  odd: to_median.at((to_median.size()+1)/2)
 *  - includes all negative values (Trials with no reactions)
 * */
double Calculation::calcMedian(Run *calc_median){
    int calculation_median = -1;
    bool get_median_value = false;  // check if getTrialAtPos can return the right Trial
    bool get_median_even = false;    // needed for the two check in an even number of Trials
    // odd_or_even is the variable to get the kind of calculation
    unsigned long odd_or_even = calc_median->getVectorSize() % 2;
    sort(calc_median->getVectorStart(), calc_median->getVectorEnd(), compareTimeFunction);       // sorting the to_median vector
    // check if the vector size is odd or even
    if(calc_median->getVectorSize() % 2){           // to_median.size % 2 = 1 -> size is odd
        unsigned int position = (calc_median->getVectorSize()+1)/2;         // calculates the position in the run_vector of run
        cout << "odd - pos at: " <<position << endl;
        Trial trial_even = calc_median->getTrialAtPos(position, &get_median_value); // get the trial for the median
        // get the reaction time for the median
        if(get_median_value){
            calculation_median = trial_even.getReactionTime();
            cout << "odd median: "<<trial_even.getReactionTime() << endl;
            return calculation_median;
        }
    }else{                      // to_median.size % 2 = 0 -> size is even
        cout<<"even"<<endl;
        Trial even_trial1 = calc_median->getTrialAtPos((calc_median->getVectorSize()/2), &get_median_value);
        Trial even_trial2 = calc_median->getTrialAtPos((calc_median->getVectorSize()/2+1), &get_median_even);
        if(get_median_value && get_median_even){
            // calculates the trial
            calculation_median = (1/2)*(even_trial1.getReactionTime()+ even_trial2.getReactionTime());
            cout << "even median: "<<median << "reactiontime1: " << even_trial1.getReactionTime() << " reactiontime2: " << even_trial2.getReactionTime() <<endl;
            return calculation_median;
        }
    }
    return calculation_median;
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
