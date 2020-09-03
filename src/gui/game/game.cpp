#include "game.h"

// Measure Class:
Measure::Measure(){
    game.setCursor(Qt::BlankCursor);
    QObject::connect(&save, SIGNAL(accepted()), this, SLOT(printHTML()));

}
// public Methods
bool Measure::Game(){
    Run *run = game.GetRun();
    QEventLoop ev;
    game.SetTest(NO_TEST);
    if(run==nullptr){
        cout << "[***] Error: Measure Game - run = nullptr no Game possible!!!" << endl;
        return false;
    }
    run->CleanMeasuredValues();
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
        PauseWindow();
    }
    game.close();
    // saving the csv file
    if(!SaveCSV())
        return false;
    // check if the user wants to print
    save.open();        // saves the measured values - if you want to print it (html)
    return true;
}

void Measure::SetMainWindowInput(QString arg_ciphre, QString arg_notice, QString arg_birthday){
    ciphre = arg_ciphre;
    notice = arg_notice;
    birthday = arg_birthday;
}

// private Methods/slots
void Measure::printHTML(){
    if(!html.CreateHTMLFile(&ciphre)){
        cout << "[***] Error: Measure - printHTML() -> can't create html file"<<endl;
        return;
    }
    if(!html.WriteHTMLFile(&c)){
        cout << "[***] Error: Measure - printHTML() -> can't write html file"<<endl;
        return;
    }
}

bool Measure::SaveCSV(){
    cout << "save csv"<<endl;
    csv.SetInformations(&ciphre, &birthday, &notice);
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

int Measure::PauseWindow(){
    QEventLoop loop;
    pause.open();
    QObject::connect(&pause, SIGNAL(finished(int)), &loop, SLOT(quit()));
    return loop.exec();
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
