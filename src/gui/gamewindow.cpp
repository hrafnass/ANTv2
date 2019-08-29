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




bool GameWindow::gameLoop(Run *r){
    cout << "Start game" << endl << "New Event to start and stop" << endl;
    for(unsigned int i = r->getPos(); r->readRun(); ++i){
        // clear screen

        // paint svgs (stars)

        // wait 1000ms

        // clear screen (stars)

        // paint arrows

        // start access to the keyPressEvent

        // wait 2000ms
    }
    return true;
}






// protected
// keyEvent (Press)
void GameWindow::keyPressEvent(QKeyEvent *event){
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


