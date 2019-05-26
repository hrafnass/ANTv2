#include "run.h"

// Public Methods
// number_of_reruns: is the number how often possibleCombinations has to used - standard is 3
// initRun fills the run_vector if the all needed Trial in a Run, normal 72 Trials
void Run::initRun(unsigned int number_of_reruns=3){
    number_of_runs = number_of_reruns;      // saves the wanted run number
    // fills the run_vector
    for(unsigned int i = 0; i < number_of_reruns; i++){
        possibleCombinations();
    }
}

void Run::newGame(){
    shuffelRun();           // shuffel the vector for a new run
    number_of_all_right_reactions = 0;  // set the number to 0 - the game isn't started yet -> no reaction is right
    setIteratorToStart();   // set the Iterator to vector.begin to iterate over it
    pos = 0;
    // reseting all measured values in run_vector (import for a second game)
    for(;it_run_vector != run_vector.begin(); ++it_run_vector) {
        // calculates the position in the vector
        pos = it_run_vector - run_vector.begin();
        // set the vector values to start
        run_vector.at(pos).setReactionTime(-1);
        run_vector.at(pos).setRightReaction(false);
    }
    setIteratorToStart();   // set the iterator to start - needed for a right use of readRun()
    pos = 0;
}

// reads every time a new trial of the run_vector
bool Run::readRun(){
    // checks if the iterator is equal run_vector.end()
    // if it's true the vector end is reached -> the run is finished and readRun has to start again (next run) -> run_vector has to be shuffel
    if(it_run_vector == run_vector.end()){
        cout << "Read Run end"<<endl;
        return false;       // is the sign to shuffle the run_vector again - the Run has ended
    }
    // saves the postion and iterates
    pos = it_run_vector - run_vector.begin();
    ++it_run_vector;

    return true;            // the retTrial is ok
}

// set the measured values
void Run::setMeasure(int reaction_time, int choose){
    cout << "setMeasure: Time: " << reaction_time << "Choose: " << choose << endl;
    run_vector.at(pos).setReactionTime(reaction_time);
    // check if the direction the same -> 0 = left; 1 = rigt
    if (run_vector.at(pos).getDirection() == choose){
        run_vector.at(pos).setRightReaction(true);
        ++number_of_all_right_reactions;    // increase the number of all right reactions
    }else
        run_vector.at(pos).setRightReaction(false);

    cout << "Runvector: " << run_vector.at(pos).getReactionTime() << endl;
}

// set the iterator to vector.begin
void Run::setIteratorToStart(){ it_run_vector = run_vector.begin(); }

//returns the actuell trial
Trial Run::getActuellTrial() {
    cout << "Actuelle Position: "<<pos<<endl;
    return run_vector.at(pos);}

/*
 * number_of_trials % number_of_trials_in_a_run = 0 -> one run is finished
 * number_of_trials_in_a_run = number_of_trials_in_run_vector / number_of_runs
 * pos starts at 0 -> number_of_trials = pos + 1
*/
bool Run::getPause(){
    cout << "getPause()" << endl;
    unsigned long vector_size = run_vector.size();      // saves the run_vector size
    if(vector_size == 0)                                // check if the vector is filled; if it isn't every pause call is true
        return false;
    unsigned long trial_number_in_run = run_vector.size() / number_of_runs;     // calculates the trials in a run - also could be a constant(72)
    unsigned long pause = (pos+1) % trial_number_in_run;    // if pos+1 is 0 a run is over
    if(pause == 0)                                      // a run is over - at the end of a run
        return true;
    return false;                                       // in a run
}

// return = true, if the trial at position pos exists, else false
// geTrialAtPos get a Trial at position pos
bool Run::getTrialAtPos(unsigned int pos, Trial *trial){
    if(pos < run_vector.size()){
        trial = &run_vector.at(pos);
        return true;
    }
    return false;
}

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
    cout << "Lenght run vector: " << run_vector.size();
}

// shuffels the run_vector - and set the iterator to run_vector_begin
void Run::shuffelRun(){
    // using the mt19937 random number generator
    shuffle(run_vector.begin(), run_vector.end(), generator);
}
