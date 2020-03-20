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
        // paint stars
        // wait and delete pixmaps
        ResetWindow(TIME_BETWEEN_ARROWS);   // 1000ms
        // restart timer - measurement
        // paint arrows
        // wait and delete pixmaps
        ResetWindow(TIME_FOR_REACTION);     // 2000ms
        // check for the break/pause/"quit test" dialog
        // if no next trial is reachable the game loop is quit
        if(run->NextTrial()){
            cout << "[***] Warning: Run->NextTrial return false in GameLoop" << endl;
            break;
        }
    }

    // qt timer
    return true;
}

// Protected Methods: Game Window
// GameLoop functions - pauses the game and delets the window
void GameWindow::ResetWindow(int arg_time){
    SleepGame(arg_time);
    DeletePixmaps();
}

// Calculations
// calculations: number of px
int GameWindow::CmToPixelNbrX(double width_in_cm){
    int dpi = GameWindow::physicalDpiX();											// get the logical dpi for width
    return static_cast<int>(((width_in_cm / INCH_IN_CM) * dpi)*GameWindow::devicePixelRatioF());	// devicePixelRatioF is the factor between logical and real pixel
}

int GameWindow::CmToPixelNbrY(double height_in_cm){
    int dpi = GameWindow::physicalDpiY();											// get the logical dpi for height
    return static_cast<int>(((height_in_cm / INCH_IN_CM) * dpi)*GameWindow::devicePixelRatioF());	// devicePixelRatioF is the factor between logical and real pixel
}

// gui and image functions
// clears all labels
void GameWindow::DeletePixmaps(){
    // iterate over all labels and clear them
    foreach(QLabel *label, this->findChildren<QLabel *>()){
        label->clear();
    }
    // paint the fixation cross
    PaintPlus();
}

// images:
// plus image
void GameWindow::PaintPlus(){
    // saves the img pos
    QString plus = PLUS_NAME;
    // calc width and height
    int w = CmToPixelNbrX(PLUS_X);
    int h = CmToPixelNbrY(PLUS_Y);
    // paint
    ui->Centreline->setFixedSize(w, h);
    ui->Centreline->setPixmap(plus);
}
