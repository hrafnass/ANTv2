#ifndef RUN_H
#define RUN_H
#include <algorithm>
#include <random>       // std::default_random_engine
#include <iostream>

#include "trial.h"

using namespace std;

/*
 * Aboute the Run-Class:
 *  - one run is made of 72 trials, which are all possible combinations of all arrow images, arrow positions and star positions
 *  - after every run the gamer could take a pause (getPause() is needed for)
 *  - the number of runs can set in run.init(number_of_runs)
 *  - the number of all possible trials only could increased, if more images and image positions added
 *  - to proof, if a run is finished, to save measured values, to read out the the trials the vector position and the vector iterator are needed
 *  - all trials of every run are saved in a run vector;
 *      Why?
 *          - the measured values are easier to calculate
 *          - the number of trials never become so big, that a modern computer couldn't handle it
 *              (for 1200 Trials max. one hour is needed - to long for an test)
 *
 * How to use  Run-Class:
 * Run run;
 * run.init(3);     // 3 runs - 72*3=216
 * newGame();       // before every new game start, to mix and reset the trials new
 *
 * while(run.readRun()){
 *      (run.getActuellTrial()).getImage();         // Imagename to load
 *      (run.getActuellTrial()).getArrowPosition(); // Position of the arrow (up, down, ...)
 *      // measure values and set them: int time, int dir
 *      run.setMeasure(time, dir);                  // saves the measurement
 * }
 */

// Run creates all all Trial for a Run and shuffels them
class Run
{
public:
    // init all start values
    Run() {
        generator.seed(rd());
        number_of_runs = 3;
        number_of_all_right_reactions = 0;
    } // init the random generator
    // methods for the run_vector
    void initRun(unsigned int); // fills all possible trials in the run_vector
    void newGame();             // create a new shuffeld, clean trial
    bool readRun();             // read an element of run_vector - bool checks if the iterator stay in the range between vector::begin and vector::end

    // setter for the measured values
    void setMeasure(int reaction_time, int choose); // saves the measured values int saves the reaction time and choose saves the value of direction (0 - left), (1 - right)
    void setIteratorToStart();  // sets the iterator to vector.begin()

    // getter for actuell trial
    Trial getActuellTrial();
    bool getPause();            // check if one of the n runs is full-filled(yes = return true; no = return false)

    // needed for searches and calculations in run_vectorrrt
    vector<Trial>::iterator getVectorEnd(){ return run_vector.end();}       // returns the end of the vectord
    vector<Trial>::iterator getVectorStart(){ return run_vector.begin();}   // returns the start of the run_vector
    unsigned long getVectorSize() { return run_vector.size();}              // returns the size of whole vector
    Trial getTrialAtPos(unsigned int pos);           // loads  the trial at the position pos from the run_vector
    unsigned int getNmbrAllRightReactions() { return number_of_all_right_reactions;}   // getter for the number

    // infos for the game users
    unsigned int getPos() { return pos;}            // return the pos oft the iterator
    unsigned int getSizeOfIterator() { return run_vector.size();}     // return the size of the iterator
private:
    void possibleCombinations();           // create all possible arrow and star combinations
    void shuffelRun();          // shuffels the run_vector (used bevor every run) - and set it_run_vector at run_vector.begin()
    vector<Trial> run_vector {};           // saves alle Trials for a Run - empty vector = start value of run_vector
    vector<Trial>::iterator it_run_vector; // the vector::iterator to iterate over the run_vector
    // pseudo random generator - if shuffelRun every time use a new generator i get every time the same shuffel
    // for shuffelRun
    random_device rd;  // the generator values aren't reproducable
    mt19937 generator; // random_generator for shuffelRun
    // saves the position of the iterator
    unsigned int pos;
    unsigned int number_of_runs;    // saves the number of runs - needed for getPause()
    unsigned int number_of_all_right_reactions;     // saves the number of all right reactions
    // starposition vector to get all posible star positions for run
    vector<Trial::star_position> star_pos_vec = { Trial::star_position::up_star, Trial::star_position::down_star, Trial::star_position::mid, Trial::star_position::both_star};
    vector<Trial::arrow_position> arrow_pos_vec = { Trial::arrow_position::up_arrow, Trial::arrow_position::down_arrow, Trial::arrow_position::both_arrow};
    vector<Trial::image> img_vec = { Trial::image::lllll, Trial::image::rrlrr, Trial::image::sslss, Trial::image::rrrrr, Trial::image::llrll, Trial::image::ssrss};
};

#endif // RUN_H
