#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <iostream>

using namespace std;


// public

// window constructor
GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    game = true;        // needed for the game loop
    training = false;   // standard setting: the gamewindow wasn't opened for exercise
}

// destructor
GameWindow::~GameWindow()
{
    delete ui;
}

//Functions
// game loop
bool GameWindow::gameLoop(){
    timer.start();  // starting the timer
    Trial t;
    game = true;
    while(run->readRun() && game){
        t = run->getActuellTrial();   // get the actuell trial
        // paint svgs (stars)
        paintStars(&t);
        // wait 1000ms
        QTimer::singleShot(TIME_BETWEEN_ARROWS, &ev, SLOT(quit())); // stops event loop for timer restart
        ev.exec();
        // clear screen (stars)
         deletePixmaps();
        // gaming time
        timer.restart();        // restarts the timer
        // paint arrows
        paintArrows(&t);
        // wait 2000 ms
        QTimer::singleShot(TIME_FOR_REACTION, &ev, SLOT(quit())); // pause the game loop for TIME_FOR_REACTION ms and then quit ev
        ev.exec();              // starts the event loop
        // clear screen
        deletePixmaps();
        // paint the break dialog, if it is possible
        paintBreakDialog();
    }    
    this->close();
    return game;
}

// protected:
// keyEvent (Press)
void GameWindow::keyPressEvent(QKeyEvent *event){
    // if the timer is not active no key press events can take
    // the measured time is > TIME_FOR_REA2000 ms or the Left or right key was pressed before
    if(timer.elapsed() > TIME_FOR_REACTION || run->getActuellTrial().getMeasure()){
        cout << "[*] No key saved." << endl;
        return;
    }
    // switch for all wanted keys
    switch (event->key()) {
    case Qt::Key_Left:
        run->setMeasure(timer.elapsed(), LEFT);     // measured time, key and that the key was pressed
        break;
    case Qt::Key_Right:
        run->setMeasure(timer.elapsed(), RIGHT);    // -"-
        break;
    default:
        cout << "[*] Wrong key" << endl;
        return;
    }
    cout << "[*] Elapsed time: " << run->getActuellTrial().getReactionTime() << endl;
}

// keyEvent (Release)
void GameWindow::keyReleaseEvent(QKeyEvent *event){
    // only needed for GameEsc
    if(event->key() == Qt::Key_Escape){
        cout << "[*] esc key - game loop quiting" << endl;
        game = false;   // quits the game loop - maybe found a better qt function
        this->close();
    }
}


// private:
// calculations: number of px 
int GameWindow::cmToPixelNbrX(double width_in_cm){
    int dpi = GameWindow::physicalDpiX();											// get the logical dpi for width
    return static_cast<int>(((width_in_cm / INCH_IN_CM) * dpi)*GameWindow::devicePixelRatioF());	// devicePixelRatioF is the factor between logical and real pixel
}

int GameWindow::cmToPixelNbrY(double height_in_cm){
    int dpi = GameWindow::physicalDpiY();											// get the logical dpi for height
    return static_cast<int>(((height_in_cm / INCH_IN_CM) * dpi)*GameWindow::devicePixelRatioF());	// devicePixelRatioF is the factor between logical and real pixel
}

// clears all labels
void GameWindow::deletePixmaps(){
	// iterate over all labels and clear them
    foreach(QLabel *label, this->findChildren<QLabel *>()){
		label->clear();
	}
    // paint the fixation cross
    paintPlus();
}

// Arrows
// paint all arrows
void GameWindow::paintArrows(Trial *t){
    QRegularExpression exp_up("UpLabel*");
    QRegularExpression exp_down("DownLabel*");

    QList<QLabel *> up_arrows = this->findChildren<QLabel *>(exp_up);
    QList<QLabel *> down_arrows = this->findChildren<QLabel *>(exp_down);

    // width and height of the "other" arrows
    int w = cmToPixelNbrX(ARROW_X);
    int h = cmToPixelNbrY(ARROW_Y);

    // paint the other images and the mid images
    if(t->getArrowPosition() == Trial::up_arrow){
        paintListLabelsArrows(up_arrows, t->getOtherImg(), w, h);
        ui->MidAbove->setPixmap(t->getMidImg());
    }else if (t->getArrowPosition() == Trial::down_arrow) {
        paintListLabelsArrows(down_arrows, t->getOtherImg(),w ,h);
        ui->MidBelow->setPixmap(t->getMidImg());
    }else if (t->getArrowPosition() == Trial::both_arrow) {
        paintListLabelsArrows(up_arrows, t->getOtherImg(), w, h);
        paintListLabelsArrows(down_arrows, t->getOtherImg(), w, h);
        ui->MidAbove->setPixmap(t->getMidImg());
        ui->MidBelow->setPixmap(t->getMidImg());
    }

    // set a fixed size for the mid labels
    ui->MidAbove->setFixedSize(w, h);
    ui->MidBelow->setFixedSize(w, h);

}

// fills the labels of the QList with img -> needed for paintStars
void GameWindow::paintListLabelsArrows(QList<QLabel *> l, QString img, int w, int h){
    // list is empty
    if(l.isEmpty())
        return;

    int pos;    // saves the pos in l
    // runs over the list and fills it with the QString image
    for(QList<QLabel*>::iterator it = l.begin(); it != l.end(); ++it){
        pos = it - l.begin();
        l.at(pos)->setFixedSize(w, h);
        l.at(pos)->setPixmap(img);
    }

}

// paints the BreakDialog
void GameWindow::paintBreakDialog(){
    // check if an pause is needed and opens the break window in foreground
    if(run->getPause()){
        BreakDialog pause;
        pause.setModal(true);
        pause.exec();
    }
}

// Star
void GameWindow::paintStars(Trial *t){
    // calculate width and height;
    int w = cmToPixelNbrX(STAR_X);
    int h = cmToPixelNbrY(STAR_Y);

    // switch instead of many ifs
    switch (t->getStarPosition()) {
    case Trial::up_star:
        paintStar(ui->MidAbove, STAR_NAME, w, h);
        break;
    case Trial::down_star:
        paintStar(ui->MidBelow, STAR_NAME, w, h);
        break;
    case Trial::both_star:
        paintStar(ui->MidAbove, STAR_NAME, w, h);
        paintStar(ui->MidBelow, STAR_NAME, w, h);
        break;
    case Trial::mid:
        paintStar(ui->Centreline, STAR_NAME,w, h);
        break;
    default:
        cout << "[*] Can't paint stars"<<endl;
        break;
    }
}

// make the star settings
void GameWindow::paintStar(QLabel *l, QString img, int w, int h){
    // set the size and paint the star
    l->setFixedSize(w, h);
    l->setPixmap(img);
    // only needed star height different to arrow heigth - explanation in gamewindow.h
    // ui->MidAbove->setFixedHeight(cmToPixelNbrY(STAR_Y));
    // ui->MidBelow->setFixedHeight(cmToPixelNbrY(STAR_Y));
}


// plus image
void GameWindow::paintPlus(){
    // saves the img pos
    QString plus = PLUS_NAME;
    // calc width and height
    int w = cmToPixelNbrX(PLUS_X);
    int h = cmToPixelNbrY(PLUS_Y);
    // paint
    ui->Centreline->setFixedSize(w, h);
    ui->Centreline->setPixmap(plus);
}
