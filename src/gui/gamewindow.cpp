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
void GameWindow::startSettings(){
    // size in px of all arrow/star labels
    int height = pixel(0.6, 'y');
    int free_width = pixel(0.6, 'y');
    int mid_height = pixel(1, 'x');
    int mid_width = pixel(1, 'y');
    // up labels
    setLabelSize(ui->Up2_1, height, free_width);
    setLabelSize(ui->Up3_2, height, free_width);
    setLabelSize(ui->Up4_3, height, free_width);
    setLabelSize(ui->Up4_5, height, free_width);
    // down labels
    setLabelSize(ui->Down2_1, height, free_width);
    setLabelSize(ui->Down2_3, height, free_width);
    setLabelSize(ui->Down3_4, height, free_width);
    setLabelSize(ui->Down4_5, height, free_width);
    // mid labels
    setLabelSize(ui->labelMid, mid_height, mid_width);
}

// private methods
int GameWindow::pixel(double cm, char x_or_y){
    int dpi = 0;
    // get the needed dpi values
    if(x_or_y == 'x')
        dpi = GameWindow::physicalDpiX();      // get the dpi values
    else if (x_or_y == 'y')
        dpi = GameWindow::physicalDpiY();
    // calculates the pixel amount
    int free_width = static_cast<int>((cm / 2.54) * dpi);
    return free_width;
}

// set the image labels
void GameWindow::setUpLables(QString other, QString mid, int arrow_width, int arrow_height){
    // sizes for up labels
    // up labels - resize the mid label - because it could changed by an star
    setLabelSize(ui->Up3, arrow_height, arrow_width);
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

void GameWindow::setDownLables(QString other, QString mid, int arrow_width, int arrow_height){
    // down labels - resize the mid label - because it could changed by an star
    setLabelSize(ui->Down3, arrow_height, arrow_width);
    // set the pixmaps
    QPixmap pix_other(other);
    QPixmap pix_mid(mid);
    // load the labels
    ui->Down1->setPixmap(pix_other);
    ui->Down2->setPixmap(pix_other);
    ui->Down3->setPixmap(pix_mid);
    ui->Down4->setPixmap(pix_other);
    ui->Down5->setPixmap(pix_other);
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

void GameWindow::setLabelSize(QLabel *label, int height, int width){
    label->setFixedHeight(height);
    label->setFixedWidth(width);
}

void GameWindow::showImgStars(Trial actuellTrial){
    // get the size for the labels
    int arrow_height = pixel(0.6, 'y');
    int arrow_width = pixel(0.6, 'x');
    QPixmap star = QPixmap(star_img);
    switch (actuellTrial.getStarPosition()) {
    case Trial::star_position::both_star:     // show the star on the Up and on the Down labels
        setLabelSize(ui->Down3, arrow_height, arrow_width);
        setLabelSize(ui->Up3, arrow_height, arrow_width);
        ui->Down3->setPixmap(star);
        ui->Up3->setPixmap(star);
        break;
    case Trial::star_position::up_star:     // shwo the star on the down labels
        setLabelSize(ui->Up3, arrow_height, arrow_width);
        ui->Up3->setPixmap(star);
        break;
    case Trial::star_position::down_star:       // show the star on the up labels
        setLabelSize(ui->Down3, arrow_height, arrow_width);
        ui->Down3->setPixmap(star);
        break;
    case Trial::star_position::mid:
        setLabelSize(ui->labelMid, arrow_height, arrow_width);
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

