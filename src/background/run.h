#ifndef RUN_H
#define RUN_H
#include <algorithm>
#include <random>       // std::default_random_engine
#include <iostream>

#include "trial.h"

using namespace std;

/*
 * How to use  Run-Class:
 * Run run;
 * run.init(2);     // 3 runs - 72*3=216
 * newGame();
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
    Run() {generator.seed(rd());} // init the random generator
    // methods for the run_vector
    void initRun(int);          // fills all possible trials in the run_vector
    void newGame();             // create a new shuffeld, clean trial
    bool readRun();             // read an element of run_vector - bool checks if the iterator stay in the range between vector::begin and vector::end
    // setter for the measured values
    void setMeasure(int reaction_time, int choose); // saves the measured values int saves the reaction time and choose saves the value of direction (0 - left), (1 - right)
    void setIteratorToStart();  // sets the iterator to vector.begin()
    // getter for actuell trial
    Trial getActuellTrial();
    bool getPause();            // check if one of the n runs is full-filled(yes = return true; no = return false)
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
    // starposition vector to get all posible star positions for run
    vector<Trial::star_position> star_pos_vec = { Trial::star_position::up_star, Trial::star_position::down_star, Trial::star_position::mid, Trial::star_position::both_star};
    vector<Trial::arrow_position> arrow_pos_vec = { Trial::arrow_position::up_arrow, Trial::arrow_position::down_arrow, Trial::arrow_position::both_arrow};
    vector<Trial::image> img_vec = { Trial::image::lllll, Trial::image::rrlrr, Trial::image::sslss, Trial::image::rrrrr, Trial::image::llrll, Trial::image::ssrss};
};

#endif // RUN_H
