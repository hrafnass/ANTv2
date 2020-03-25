#include "game.h"

// Measure Class:
// public Methods
bool Measure::Game(){
    Run *run = game.GetRun();
    if(run==nullptr){
        cout << "[***] Error: Measure Game - run = nullptr no Game possible!!!" << endl;
        return false;
    }
    run->SetMeasuredValues(-1, false, false);
    game.showFullScreen();
    // normal Game
    for(unsigned int i = 0; i < game.GetNbrOfRuns(); ++i){
        if(!game.GameLoop(TRIALS_IN_RUN_GAME)){
            cout << "[***] Error: Error in Game Loop - Measure Class!" << endl;
            game.close();
            return false;
        }
        pause.open();   // pause between the runs
    }
    game.close();
    // saving the csv file

    // check if the user wants to print
    //save.open();        // saves the measured values - if you want to print it (html)
    return true;
}

void Measure::SetMainWindowInput(QString arg_forename, QString arg_name, QString arg_notice, QString arg_birthday){
    forename = arg_forename;
    name = arg_name;
    notice = arg_notice;
    birthday = arg_birthday;
}

// protected Methods

// Test Class
// public Methods+Constructor
//TestGame Constructor
bool TestGame::Game(){
    Run *run = game.GetRun();
    if(run==nullptr){
        cout << "[***] Error: Measure Game - run = nullptr no Game possible!!!" << endl;
        return false;
    }
    run->CleanMeasuredValues();
    // Test Game
    game.showFullScreen();
    for(unsigned int i = 0; i < game.GetNbrOfRuns(); ++i){
        if(!game.GameLoop(TRIALS_IN_RUN_TEST)){
            cout << "[***] Error: Error in Game Loop - TestGame Class!" << endl;
            game.close();
            return false;
        }
    }
    //arg_excercise->open();
    game.close();
    return true;
}
