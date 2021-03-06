/* ANTv2
 * Copyright (C) 2020 Siegfried Gauggel
 * Copyright (C) 2020 Marcel Gräfenstein
 * 
 * This file is part of ANTv2.
 * 
 * ANTv2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * ANTv2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with ANTv2.  If not, see <https://www.gnu.org/licenses/>.
 */


#include "game.h"

// Measure Class:
Measure::Measure(){
    game.setCursor(Qt::BlankCursor);
    QObject::connect(&save, SIGNAL(accepted()), this, SLOT(printHTML()));

}
// public Methods
bool Measure::Game(){
    run = game.GetRun();
    // check, if run is created correct
    if(run == nullptr)
        return false;
    // eventloop
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
    /* check if the user wants to print the calculated values
     * if GetRunLoop() == false the game was quit with ESC ->
     * the value calculation is senseless, because the test person
     * hasn't react to all arrows.
     */
    if(game.GetRunLoop())
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
    QDate d = csv.GetDate();
    QTime t = csv.GetTime();

    if(!js.CreateJSFile(&ciphre, &d, &t)){
        cout << "[***] Error: Measure - printHTML() -> can't create html file"<<endl;
        return;
    }
    if(!js.WriteJSFile(run)){
        cout << "[***] Error: Measure - printHTML() -> can't write html file"<<endl;
        return;
    }
}

bool Measure::SaveCSV(){
    csv.SetTimeAndDate();
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
