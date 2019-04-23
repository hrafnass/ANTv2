#include "run.h"

// Public Methods
// number_of_reruns: is the number how often possibleCombinations has to used - standard is 2
// initRun fills the run_vector if the all needed Trial in a Run, normal 96 Trials
void Run::initRun(int number_of_reruns=2){
    // fills the run_vector
    for(int i = 0; i < number_of_reruns; i++){
        possibleCombinations();
    }
}

void Run::newGame(){
    shuffelRun();
    pos = 0;
    for(;it_run_vector != run_vector.begin(); ++it_run_vector) {
        // calculates the position in the vector
        pos = it_run_vector - run_vector.begin();
        // set the vector values to start
        run_vector.at(pos).setReactionTime(-1);
        run_vector.at(pos).setRightReaction(false);
    }
    // set the iterator to begin
    it_run_vector = run_vector.begin();
    pos = 0;
}

// reads every time a new trial of the run_vector
bool Run::readRun(){
    // checks if the iterator is equal run_vector.end()
    // if it's true the vector end is reached -> the run is finished and readRun has to start again (next run) -> run_vector has to be shuffel
    if(it_run_vector == run_vector.end())
        return false;       // is the sign to shuffle the run_vector again - the Run has ended
    // saves the postion and iterates
    pos = it_run_vector - run_vector.begin();
    ++it_run_vector;

    return true;            // the retTrial is ok
}

// set the measured values
void Run::setMeasure(int reaction_time, int choose){
    run_vector.at(pos).setReactionTime(reaction_time);
    // check if the direction the same -> 0 = left; 1 = rigt
    if (run_vector.at(pos).getDirection() == choose)
        run_vector.at(pos).setRightReaction(true);
    else
        run_vector.at(pos).setRightReaction(false);
}


//returns the actuell trial
Trial Run::getActuellTrial() {
    cout << "Actuelle Position: "<<pos<<endl;
    return run_vector.at(pos);}

// Private Methods
// create 48 possible Trials - all combinations of images and arrow and star positions
// 6 pictures * 2 arrow positions * 4 star positions = 48 Trials
void Run::possibleCombinations(){
    // iterate over all possible arrow combination
    for(auto it_img : img_vec){
        // iterate over all posible arrow positions (above/under the plus image)
        for(auto it_ar_pos : arrow_pos_vec) {
            // iterate over all star image positions
            for(auto it_star_pos : star_pos_vec){
                run_vector.push_back(Trial(it_star_pos, it_ar_pos, it_img));
            }
        }
    }
}

// shuffels the run_vector - and set the iterator to run_vector_begin
void Run::shuffelRun(){
    // using the mt19937 random number generator
    shuffle(run_vector.begin(), run_vector.end(), generator);
    // set the run_vector iterator to the start
    it_run_vector = run_vector.begin();
}
