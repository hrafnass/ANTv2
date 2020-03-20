#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <iostream>

using namespace std;

// public Methods: GameWindow
bool GameWindow::GameLoop(int arg_pass_number){
    // check if run is filled
    if(run == nullptr){
        cout << "[***] Error: No Run-Object is loaded!" << endl;
        return false;
    }

    // clean run and get the first Trial
    bool in_size = false;                   // check if the actuell vector.size > 0
    run->CleanMeasuredValues();
    Trial actuell_trial = run->GetTrial(&in_size);
    if(!in_size){
        cout << "[***] Error: Vector Size is 0!" << endl;
        return false;
    }
    // sets the run_length number, if it doesn't fit
    if(run->GetRunLength() != arg_pass_number)
        run->SetRunLength(arg_pass_number);

    // runs so long run (run_length) it allows
    for(unsigned int i=0; i < run->GetRunLength(); ++i){

    }

    // qt timer

    return true;
}

