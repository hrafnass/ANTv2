#include "game.h"

// Measure Class:
// public Methods
bool Measure::Game(){
    Run *run = game.GetRun();
    game.SetTest(NO_TEST);
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
            if(!SaveCSV())
                return false;
            game.close();
            return false;
        }
        pause.open();   // pause between the runs
    }
    game.close();
    // saving the csv file
    if(!SaveCSV())
        return false;
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

// private Methods
bool Measure::SaveCSV(){
    cout << "save csv"<<endl;
    csv.SetInformations(&name, &forename, &birthday, &notice);
    if(!csv.CreateCSVFile()){
        cout << "[***] Error: Measure - SaveCSV() -> can't create csv file"<<endl;
        return false;
    }
    if(!csv.WriteCSVFile(game.GetRun())){
        cout << "[***] Error: Measure - SaveCSV() -> can't write into csv file"<<endl;
        return false;
    }
    return true;
}


// protected Methods

// Test Class
// public Methods+Constructor
//TestGame Constructor
bool TestGame::Game(){
    Run *run = game.GetRun();
    game.SetTest(TEST);
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
    game.close();
    return true;
}
