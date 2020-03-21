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
// The GameLoop Method runs one run after this a pause is possible
// return true: One Run is reached successfully
// return false: trials for the run aren't set right
bool GameWindow::GameLoop(int arg_one_run){
    // check if run is filled
    if(run == nullptr){
        cout << "[***] Error: No Run-Object is loaded!" << endl;
        return false;
    }
    
    // check if the size of one run is usable
    if(arg_one_run <= 0 || arg_one_run > run->GetRunLength()){
        cout << "[***] Error: The One Run Value: "<< arg_one_run << " can't used!" << endl;
        return false;
    }

    // check if the game reached the end
    if(run->GetRunLength() == (run->GetPosition()+1))
        return true;

    // clean run and get the first Trial
    bool in_size = false;                   // check if the actuell vector.size > 0
    Trial actuell_trial = run->GetTrial(&in_size);
    if(!in_size){
        cout << "[***] Error: Vector Size is 0!" << endl;
        return false;
    }

    // runs so long a multiple from arg_one_run is reached
    for(unsigned int i=0; i < (run->GetRunLength()%arg_one_run); ++i){
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

void GameWindow::SetPassNbr(int arg_pass_number){
    // sets the run_length number, if it doesn't fit
    if(run->GetRunLength() != arg_pass_number)
        run->SetRunLength(arg_pass_number);
}

// Protected Methods: Game Window
// keyPress Methods
// keyEvent (Press)
void GameWindow::keyPressEvent(QKeyEvent *event){
    bool check = false;
    // if the timer is not active no key press events can take
    if(timer.elapsed() > TIME_FOR_REACTION){    // the measured time is > TIME_FOR_REA2000 ms
        cout << "[*] No key saved." << " - excercise number: " << (run->GetPosition()+1) << endl;
        return;
    }
    // check if a key (left or right) was pressed before then we don't take a new anwser
    if(run->GetTrial(&check).GetPressed()){
        cout << "[*] Key was pressed before!" << endl;
        return;
    }
    // switch for all wanted keys
    switch (event->key()) {
    case Qt::Key_Left:
        SaveMeasuredValues(TrialComponents::DirectionMidArrow::left);
        break;
    case Qt::Key_Right:
        SaveMeasuredValues(TrialComponents::DirectionMidArrow::right);
        break;
    default:
        cout << "[*] Wrong key" << endl;
        return;
    }
}

// keyEvent (Release)
void GameWindow::keyReleaseEvent(QKeyEvent *event){
    // only needed for GameEsc
    if(event->key() == Qt::Key_Escape){
        cout << "[*] esc key - game loop quiting" << endl;
        run->SetRunLength(-1);  // no new run can be started
        this->close();
    }
}

void GameWindow::SaveMeasuredValues(TrialComponents::DirectionMidArrow arg_direction){
    bool check = false;
    if(arg_direction == run->GetTrial(&check).GetDirectionMidArrow()){
        run->SetMeasuredValues(timer.elapsed(), true, true);
    }else {
        run->SetMeasuredValues(timer.elapsed(), false, true);
    }
}


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
// paints a Trial
void GameWindow::PaintStars(Trial *arg_trial){
    // calculate width and height;
        int w = CmToPixelNbrX(STAR_X);
        int h = CmToPixelNbrY(STAR_Y);

        // switch instead of many ifs
        switch (arg_trial->GetCue()) {
        case TrialComponents::Cue::spatial_cue_up:
            paintStar(ui->MidAbove, STAR, w, h);
            break;
        case TrialComponents::Cue::spatial_cue_down:
            paintStar(ui->MidBelow, STAR, w, h);
            break;
        case TrialComponents::Cue::double_cue:
            paintStar(ui->MidAbove, STAR, w, h);
            paintStar(ui->MidBelow, STAR, w, h);
            break;
        case TrialComponents::Cue::center_cue:
            paintStar(ui->Centreline, STAR,w, h);
            break;
        case TrialComponents::Cue::non_cue:
            cout << "[*] Nearly the same like default - no cue is printed" << endl;
            break;
        default:
            cout << "[*] Can't paint stars"<<endl;
            break;
        }
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

// Measure Class:
// public Methods

// protected Methods

// Test Class
// public Methods

// protected Methods - override ResetWindow
void Test::ResetWindow(int arg_time){
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
