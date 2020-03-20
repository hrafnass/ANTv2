#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <iostream>

using namespace std;

// public Methods: GameWindow
bool GameWindow::GameLoop(){
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

    // qt timer

    return true;
}

