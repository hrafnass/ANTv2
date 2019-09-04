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
        // clear screen
        deletePixmaps();
        // paint svgs (stars)
        QTimer::singleShot(TIME_BETWEEN_ARROWS, &ev, SLOT(quit())); // stops event loop for timer restart
        // clear screen (stars)
        deletePixmaps();
        // paint arrows
        t = r->getActuellTrial();
        paintArrows(&t);
        // gaming time
        timer.restart();        // restarts the timer
        ev.exec();              // starts the event loop
        QTimer::singleShot(TIME_FOR_REACTION, &ev, SLOT(quit())); // pause the game loop for TIME_FOR_REACTION ms and then quit ev
        ev.exec();          // activate the event loop - needed for ESC
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
        paintListLabels(up_arrows, t->getOtherImg(), w, h);
        ui->MidAbove->setPixmap(t->getMidImg());
    }else if (t->getArrowPosition() == Trial::down_arrow) {
        cout << "Down Arrows" << endl;
        paintListLabels(down_arrows, t->getOtherImg(),w ,h);
        ui->MidBelow->setPixmap(t->getMidImg());
    }else if (t->getArrowPosition() == Trial::both_arrow) {
        cout << "Both Arrows" << endl;
        paintListLabels(up_arrows, t->getOtherImg(), w, h);
        paintListLabels(down_arrows, t->getOtherImg(), w, h);
        ui->MidAbove->setPixmap(t->getMidImg());
        ui->MidBelow->setPixmap(t->getMidImg());
    }

    // set a fixed size for the mid labels
    ui->MidAbove->setFixedSize(w, h);
    ui->MidBelow->setFixedSize(w, h);

}

// fills the labels of the QList with img -> needed for paintStars
void GameWindow::paintListLabels(QList<QLabel *> l, QString img, int w, int h){
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
    // switch instead of many ifs
    switch (t->getStarPosition()) {
    case Trial::up_star:
        break;
    case Trial::down_star:
        break;
    case Trial::both_star:
        break;
    case Trial::mid:
        break;
    default:
        cout << "Can't paint stars"<<endl;
        break;
    }
}
