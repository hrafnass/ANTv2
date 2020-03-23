#include "game.h"

// Measure Class:
// public Methods
bool Measure::Game(){
    if(run==nullptr){
        cout << "[***] Error: Measure Game - run = nullptr no Game possible!!!" << endl;
        return false;
    }
    run->SetMeasuredValues(-1, false, false);
    // normal Game
    for(unsigned int i = 0; i < number_of_runs; ++i){
        if(!GameLoop(TRIALS_IN_RUN_GAME)){
            cout << "[***] Error: Error in Game Loop - Measure Class!" << endl;
            return false;
        }
        pause.open();   // pause between the runs
    }
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
/*TestGame::TestGame(){
    connect(&excercise,SIGNAL(buttonPressed()), this, SLOT(on_action_bung_triggered()));
}*/

bool TestGame::Game(){
    if(run==nullptr){
        cout << "[***] Error: Measure Game - run = nullptr no Game possible!!!" << endl;
        return false;
    }
    run->SetMeasuredValues(-1, false, false);
    // Test Game
    for(unsigned int i = 0; i < number_of_runs; ++i){
        if(!GameLoop(TRIALS_IN_RUN_TEST)){
            cout << "[***] Error: Error in Game Loop - Measure Class!" << endl;
            return false;
        }
    }
    excercise.open();

    return true;
}

// SLOT
void TestGame::on_action_excercise_triggered(){
    if(!Game()){
        cout << "[***] Error: TestGame Error!!!" << endl;
        return;
    }
    // ask the user for a new excercise
    excercise.setModal(true);
    excercise.show();
}

// protected Methods - override ResetWindow
void TestGame::ResetWindow(int arg_time){
    bool check = false;
    QString right_or_wrong_smile;   // saves the smile paths
    GameWindow::ResetWindow(arg_time);
    // if a key was pressed - show a smile
    if(!(run->GetTrial(&check)).GetPressed())
        return;
    // saves the picture path in right_or_wrong_smile
    if((run->GetTrial(&check)).GetReaction())           // happy smile
        right_or_wrong_smile = CORRECT;
    else                                                // sad smile
        right_or_wrong_smile = WRONG;
    // paint the picture
    ui->Centreline->setPixmap(right_or_wrong_smile);
}
