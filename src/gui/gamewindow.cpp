#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <iostream>

using namespace std;

GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
}

GameWindow::~GameWindow()
{
    delete ui;
}

// public methods
void GameWindow::setRun(Run *r){ run = r;}

// protected methods
// adds the key press event
void GameWindow::keyPressEvent(QKeyEvent *event){
    run->readRun();
    // catch the pressed key only left and right are needed
    switch (event->key()) {
    case Qt::Key_Left:      // pressed left key
        run->setMeasure(100, 0);
        imgLoader(STAR);
        break;
    case Qt::Key_Right:     // pressed right key
        run->setMeasure(50, 1);
        imgLoader(ARROW);
        break;
    case Qt::Key_Escape:
        cout << "Game ESC";
        // show the save dialog
        save.setModal(true);
        save.exec();
        this->close();      // mit esc wird das fenster geschlossen
        break;
    default:                // pressed false key, mabye do nothing or
        cout << "wrong key";
        break;
    }
    cout << "Right Reaction " << run->getActuellTrial().getRightReaction() << endl;
}

// set the width and height of the labels for an 1,6 cm long arrow and 0,6 cm free spaces between
void GameWindow::setLabelSize(){
    // calculate the size in cm to px
    // number of px = size [cm] / 2,54 [cm/i] x [dpi]
    int x_dpi = GameWindow::physicalDpiX();      // get the dpi values
    int y_dpi = GameWindow::physicalDpiY();
    // size in px of all arrow labels
    int arrow_height = static_cast<int>((0.6 / 2.54) * y_dpi);
    int arrow_width = static_cast<int>((1.6 / 2.54) * x_dpi);
    int free_height = static_cast<int>((0.6 / 2.54) * y_dpi);
    int free_width = static_cast<int>((0.6 / 2.54) * x_dpi);
    // sizes for up labels
    ui->Up1->setFixedHeight(arrow_height);
    ui->Up1->setFixedWidth(arrow_width);
    ui->Up2->setFixedHeight(arrow_height);
    ui->Up2->setFixedWidth(arrow_width);
    ui->Up2_1->setFixedHeight(free_height);
    ui->Up2_1->setFixedWidth(free_width);
    ui->Up3->setFixedHeight(arrow_height);
    ui->Up3->setFixedWidth(arrow_width);
    ui->Up4->setFixedHeight(arrow_height);
    ui->Up4->setFixedWidth(arrow_width);
    ui->Up3_2->setFixedHeight(free_height);
    ui->Up3_2->setFixedWidth(free_width);
    ui->Up5->setFixedHeight(arrow_height);
    ui->Up5->setFixedWidth(arrow_width);
    ui->Up4_3->setFixedHeight(free_height);
    ui->Up4_3->setFixedWidth(free_width);
    ui->Up4_5->setFixedHeight(free_height);
    ui->Up4_5->setFixedWidth(free_width);
    // sizes for downlabels
    ui->Down1->setFixedHeight(arrow_height);
    ui->Down1->setFixedWidth(arrow_width);
    ui->Down2->setFixedHeight(arrow_height);
    ui->Down2->setFixedWidth(arrow_width);
    ui->Down2_1->setFixedHeight(free_height);
    ui->Down2_1->setFixedWidth(free_width);
    ui->Down3->setFixedHeight(arrow_height);
    ui->Down3->setFixedWidth(arrow_width);
    ui->Down4->setFixedHeight(arrow_height);
    ui->Down4->setFixedWidth(arrow_width);
    ui->Down2_3->setFixedHeight(free_height);
    ui->Down2_3->setFixedWidth(free_width);
    ui->Down5->setFixedHeight(arrow_height);
    ui->Down5->setFixedWidth(arrow_width);
    ui->Down3_4->setFixedHeight(free_height);
    ui->Down3_4->setFixedWidth(free_width);
    ui->Down4_5->setFixedHeight(free_height);
    ui->Down4_5->setFixedWidth(free_width);
}

// private methods
// set the image labels
void GameWindow::setUpLables(QString other, QString mid){
    // set the pixmaps
    QPixmap pix_other(other);
    QPixmap pix_mid(mid);
    // load the labels
    ui->Up1->setPixmap(pix_other);
    ui->Up2->setPixmap(pix_other);
    ui->Up3->setPixmap(pix_mid);
    ui->Up4->setPixmap(pix_other);
    ui->Up5->setPixmap(pix_other);
}

void GameWindow::setDownLables(QString other, QString mid){
    // set the pixmaps
    QPixmap pix_other(other);
    QPixmap pix_mid(mid);
    // load the labels
    ui->Down1->setPixmap(other);
    ui->Down2->setPixmap(other);
    ui->Down3->setPixmap(mid);
    ui->Down4->setPixmap(other);
    ui->Down5->setPixmap(other);
}

void GameWindow::clearScreen(){
    QPixmap free(":/ressources/images/free_space.svg");
    ui->Down1->setPixmap(free);
    ui->Down2->setPixmap(free);
    ui->Down3->setPixmap(free);
    ui->Down4->setPixmap(free);
    ui->Down5->setPixmap(free);
    ui->Up1->setPixmap(free);
    ui->Up2->setPixmap(free);
    ui->Up3->setPixmap(free);
    ui->Up4->setPixmap(free);
    ui->Up5->setPixmap(free);
    //ui->labelMid->setPixmap(free);
}

void GameWindow::showImgArrow(Trial actuellTrial){
    switch (actuellTrial.getArrowPosition()) {
    case Trial::arrow_position::both_arrow:     // show the Trial on the Up and on the Down labels
        setDownLables(actuellTrial.getOtherImg(), actuellTrial.getMidImg());    // load the images
        setUpLables(actuellTrial.getOtherImg(), actuellTrial.getMidImg());
        break;
    case Trial::arrow_position::down_arrow:     // shwo the Trial on the down labels
        setDownLables(actuellTrial.getOtherImg(), actuellTrial.getMidImg());    // load the images
        break;
    case Trial::arrow_position::up_arrow:       // show the Trial on the up labels
        setUpLables(actuellTrial.getOtherImg(), actuellTrial.getMidImg());
        break;
    default:
        cout << "Error in showImgArrow - ArrowPosition isn't set right!!!";
        break;
    }
}

void GameWindow::showImgStars(Trial actuellTrial){
    QPixmap star = QPixmap(star_img);
    switch (actuellTrial.getStarPosition()) {
    case Trial::star_position::both_star:     // show the star on the Up and on the Down labels
        ui->Down3->setPixmap(star);
        ui->Up3->setPixmap(star);
        break;
    case Trial::star_position::up_star:     // shwo the star on the down labels
        ui->Up3->setPixmap(star);
        break;
    case Trial::star_position::down_star:       // show the star on the up labels
        ui->Down3->setPixmap(star);
        break;
    case Trial::star_position::mid:
        ui->labelMid->setPixmap(star);
        break;
    default:
        break;
    }
}

// loads the images for the game
void GameWindow::imgLoader(bool img) {
    // clear the screen and get the actuell Trial
    clearScreen();
    Trial actuellTrial = run->getActuellTrial();
    // run the image load function for arrows and stars
    if(img == STAR)
        showImgStars(actuellTrial);
    else if (img == ARROW)
        showImgArrow(actuellTrial);
}

