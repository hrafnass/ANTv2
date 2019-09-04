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
}

// destructor
GameWindow::~GameWindow()
{
    delete ui;
}

//Functions
// game loop
bool GameWindow::gameLoop(Run *r){
    timer.start();  // starting the timer
    Trial t;
    while(r->readRun()){
        t = r->getActuellTrial();   // get the actuell trial
        // clear screen
        deletePixmaps();
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
    }
    this->close();
    return true;
}


// protected:
// keyEvent (Press)
void GameWindow::keyPressEvent(QKeyEvent *event){
    // if the timer is not active no key press events can take
    if(timer.elapsed() < TIME_FOR_REACTION){
        cout << "Timer is not Active" << endl;
        return;
    }
    // switch for all wanted keys
    switch (event->key()) {
    case Qt::Key_Left:
        cout << "left key" << endl;
        break;
    case Qt::Key_Right:
        cout << "right key" << endl;
        break;
    case Qt::Key_Escape:
        cout << "Wrong key" << endl;
        return;
    }
    ev.quit();      // stop the event loop after the first left or right key was pressed
}

// keyEvent (Release)
void GameWindow::keyReleaseEvent(QKeyEvent *event){
    // only needed for GameEsc
    if(event->key() == Qt::Key_Escape){
        cout << "ESC released" << endl;
        this->close();
    }
}


// private:
// calculations: number of px 
int GameWindow::cmToPixelNbrX(double width_in_cm){
	int dpi = GameWindow::logicalDpiX();											// get the logical dpi for width
    return static_cast<int>(((width_in_cm / INCH_IN_CM) * dpi)*GameWindow::devicePixelRatioF());	// devicePixelRatioF is the factor between logical and real pixel
}

int GameWindow::cmToPixelNbrY(double height_in_cm){
	int dpi = GameWindow::logicalDpiY();											// get the logical dpi for height
    return static_cast<int>(((height_in_cm / INCH_IN_CM) * dpi)*GameWindow::devicePixelRatioF());	// devicePixelRatioF is the factor between logical and real pixel
}

// clears all labels
void GameWindow::deletePixmaps(){
	// iterate over all labels and clear them
    foreach(QLabel *label, this->findChildren<QLabel *>()){
		label->clear();
	}
}

// Arrows
// paint all arrows
void GameWindow::paintArrows(Trial *t){
    QRegularExpression exp_up("UpLabel*");
    QRegularExpression exp_down("DownLabel*");

    QList<QLabel *> up_arrows = this->findChildren<QLabel *>(exp_up);
    QList<QLabel *> down_arrows = this->findChildren<QLabel *>(exp_down);

    cout << "UP: " << up_arrows.size() << " DOWN: " << down_arrows.size() << endl;

    // width and height of the "other" arrows
    int w = cmToPixelNbrX(ARROW_X);
    int h = cmToPixelNbrY(ARROW_Y);

    // paint the other images and the mid images
    if(t->getArrowPosition() == Trial::up_arrow){
        cout << "Up Arrows" << endl;
        paintListLabelsArrows(up_arrows, t->getOtherImg(), w, h);
        ui->MidAbove->setPixmap(t->getMidImg());
    }else if (t->getArrowPosition() == Trial::down_arrow) {
        cout << "Down Arrows" << endl;
        paintListLabelsArrows(down_arrows, t->getOtherImg(),w ,h);
        ui->MidBelow->setPixmap(t->getMidImg());
    }else if (t->getArrowPosition() == Trial::both_arrow) {
        cout << "Both Arrows" << endl;
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

// Star
void GameWindow::paintStars(Trial *t){
    // calculate width and height;
    int w = cmToPixelNbrX(STAR_X);
    int h = cmToPixelNbrY(STAR_Y);

    // switch instead of many ifs
    switch (t->getStarPosition()) {
    case Trial::up_star:
        paintStar(ui->MidAbove,":/ressources/images/star.svg", w, h);
        cout << "up star"<<endl;
        break;
    case Trial::down_star:
        paintStar(ui->MidBelow, ":/ressources/images/star.svg", w, h);
        cout << "down star"<<endl;
        break;
    case Trial::both_star:
        paintStar(ui->MidAbove, ":/ressources/images/star.svg", w, h);
        paintStar(ui->MidBelow, ":/ressources/images/star.svg", w, h);
        cout << "both star"<<endl;
        break;
    case Trial::mid:
        paintStar(ui->Centreline, ":/ressources/images/star.svg",w, h);
        cout << "mid star"<<endl;
        break;
    default:
        cout << "Can't paint stars"<<endl;
        break;
    }
}

// make the star settings
void GameWindow::paintStar(QLabel *l, QString img, int w, int h){
    // set the size and paint the star
    l->setFixedSize(w, h);
    l->setPixmap(img);
}
