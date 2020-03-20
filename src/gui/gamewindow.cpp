#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <iostream>

using namespace std;

// window constructor
GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    /* We need a fixed size between arrows and the plus img. Important for the game.
     * I take 1 inch (2 cm) for the distance between arrows and plus.
     * We only need to change the height. The width doesn't interest.
     * -> w, expanding aren't needed; only h and fixed
     **/
    // calcs the needed px size
    int w = CmToPixelNbrX(DISTANCE_ARROW_PLUS_X);
    int h = CmToPixelNbrY(DISTANCE_ARROW_PLUS_Y);
    // changes the size
    ui->verticalSpacerUpMid->changeSize(w, h, QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui->verticalSpacerDownMid->changeSize(w, h, QSizePolicy::Expanding, QSizePolicy::Fixed);
}

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

// sets the GameLoop in a SleepModus
void GameWindow::SleepGame(int arg_sleep_time){
    // pause the game loop for sleep_time ms and then quit ev
    QTimer::singleShot(arg_sleep_time, &ev, SLOT(quit()));
    ev.exec();              // starts the event loop
}

// Calculations
// calculations: number of px
int GameWindow::CmToPixelNbrX(double arg_width_in_cm){
    int dpi = GameWindow::physicalDpiX();											// get the logical dpi for width
    return static_cast<int>(((arg_width_in_cm / INCH_IN_CM) * dpi)*GameWindow::devicePixelRatioF());	// devicePixelRatioF is the factor between logical and real pixel
}

int GameWindow::CmToPixelNbrY(double arg_height_in_cm){
    int dpi = GameWindow::physicalDpiY();											// get the logical dpi for height
    return static_cast<int>(((arg_height_in_cm / INCH_IN_CM) * dpi)*GameWindow::devicePixelRatioF());	// devicePixelRatioF is the factor between logical and real pixel
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
