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
    // label lists of lists up and down
    QRegularExpression exp_up("UpLabel*");
    QRegularExpression exp_down("DownLabel*");

    up_arrows = this->findChildren<QLabel *>(exp_up);
    down_arrows = this->findChildren<QLabel *>(exp_down);

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
    // set the standard value for runs - game
    number_of_runs = NBR_OF_RUNS_GAME;
}

// destructor
GameWindow::~GameWindow()
{
    delete ui;
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
    // Delete everythind
    DeletePixmaps();

    timer.start();  // starts the timer
    // runs so long a multiple from arg_one_run is reached
    for(int i=0; i < arg_one_run; ++i){
        // paint stars
        Trial actuell_trial = run->GetTrial(&in_size);
        PaintStars(&actuell_trial);
        // wait and delete pixmaps
        ResetWindow(TIME_BETWEEN_ARROWS);   // 1000ms
        // restart timer - measurement
        timer.restart();
        // paint arrows
        PaintArrows(&actuell_trial);
        // wait and delete pixmaps
        ResetWindow(TIME_FOR_REACTION);     // 2000ms
        // if no next trial is reachable the game loop is quit
        cout << "Position GameLoop RUn "<<run->GetPosition()<<endl;
        if(!run->NextTrial()){
            cout << "[***] Warning: Run->NextTrial return false in GameLoop" << endl;
            break;
        }
    }

    // qt timer
    return true;
}
// set the the game
void GameWindow::SetGame(Run *arg_run, int arg_pass_number, unsigned int arg_nbr_of_runs){
    SetRun(arg_run);
    SetPassNbr(arg_pass_number);
    SetNbrOfRuns(arg_nbr_of_runs);
}

void GameWindow::SetPassNbr(int arg_pass_number){
    // sets the run_length number, if it doesn't fit
    if(run->GetRunLength() != arg_pass_number)
        run->SetRunLength(arg_pass_number);
}

// number of runs setter
void GameWindow::SetNbrOfRuns(unsigned int arg_nbr_of_runs){
    if(arg_nbr_of_runs > 0)
        number_of_runs = arg_nbr_of_runs;
    else
        number_of_runs = NBR_OF_RUNS_GAME;   // standard
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

// private Mehtods
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
            PaintStar(ui->MidAbove, STAR, w, h);
            break;
        case TrialComponents::Cue::spatial_cue_down:
            PaintStar(ui->MidBelow, STAR, w, h);
            break;
        case TrialComponents::Cue::double_cue:
            PaintStar(ui->MidAbove, STAR, w, h);
            PaintStar(ui->MidBelow, STAR, w, h);
            break;
        case TrialComponents::Cue::center_cue:
            PaintStar(ui->Centreline, STAR,w, h);
            break;
        case TrialComponents::Cue::non_cue:
            cout << "[*] Nearly the same like default - no cue is printed" << endl;
            break;
        default:
            cout << "[*] Can't paint stars"<<endl;
            break;
        }
}

// make the star setting and paint the star
void GameWindow::PaintStar(QLabel *arg_label, QString arg_img_name, int arg_w, int arg_h){
    // set the size and paint the star
    arg_label->setFixedSize(arg_w, arg_h);
    arg_label->setPixmap(arg_img_name);
    // only needed star height different to arrow heigth - explanation in gamewindow.h
    // ui->MidAbove->setFixedHeight(cmToPixelNbrY(STAR_Y));
    // ui->MidBelow->setFixedHeight(cmToPixelNbrY(STAR_Y));
}

// paints an arrow
void GameWindow::PaintArrows(Trial *arg_trial){
    // width and height of the "other" arrows
    int w = CmToPixelNbrX(ARROW_X);
    int h = CmToPixelNbrY(ARROW_Y);

    // paint the other images and the mid images
    switch (arg_trial->GetArrowPositions()) {
    case TrialComponents::ArrowPositions::up:       // paints the arrow over the cross
        cout << "[****] DEBUG: ARROW UP " <<endl;
        PaintListLabelsArrows(up_arrows, arg_trial, w, h);
        break;
    case TrialComponents::ArrowPositions::down:     // paints the arrows under the cross
        cout << "[****] DEBUG: ARROW DOWN " <<endl;
        PaintListLabelsArrows(down_arrows, arg_trial, w, h);
        break;
    default:
        cout << "[***] Error: This ArrowPosition doesn't exists!!!" << endl;
    }
}

// images:
// paint a list of arrows
void GameWindow::PaintListLabelsArrows(QList<QLabel *> arg_list, Trial *arg_trial, int arg_w, int arg_h){
    // list is empty
    if(arg_list.isEmpty()){
        cout << "[***] Error: Empty Label List!!!"<<endl;
        return;
    }

    int pos;    // saves the pos in l
    // runs over the list and fills it with the QString image
    for(QList<QLabel*>::iterator it = arg_list.begin(); it != arg_list.end(); ++it){
        pos = it - arg_list.begin();
        // paint all outer images
        arg_list.at(pos)->setFixedSize(arg_w, arg_h);
        arg_list.at(pos)->setPixmap(arg_trial->GetOuterArrow());
    }
    // paints the mid image
    if(arg_trial->GetArrowPositions() == TrialComponents::ArrowPositions::up){
        ui->MidAbove->setFixedSize(arg_w, arg_h);
        ui->MidAbove->setPixmap(arg_trial->GetInnerArrow());
    }else {
        ui->MidBelow->setFixedSize(arg_w, arg_h);
        ui->MidBelow->setPixmap(arg_trial->GetInnerArrow());
    }
}

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
