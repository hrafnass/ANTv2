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


bool GameWindow::gameLoop(Run *r){

    for(unsigned int i = r->getPos(); r->readRun(); ++i){
        // clear screen

        // paint svgs (stars)

        // wait 1000ms

        // clear screen (stars)

        // paint arrows

        // start access to the keyPressEvent

        // wait 2000ms
    }

}






// protected
// keyEvent
void GameWindow::keyPressEvent(QKeyEvent *event){
    // need a measure function - and only the first press should saved
    if(event->key() == Qt::Key_Left){
        cout << "pressed left key" << endl;
    }

    if(event->key() == Qt::Key_Right){
        cout << "pressed right key" << endl;
    }
}
