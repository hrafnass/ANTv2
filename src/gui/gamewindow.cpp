#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <iostream>
#include <stdio.h>

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
    timer.start();  // starting the timer
    for(; r->readRun();){
        // clear screen

        // paint svgs (stars)

        QTimer::singleShot(TIME_BETWEEN_ARROWS, printf("Waiting 1000ms")); // wait 1000ms


        // clear screen (stars)

        // paint arrows
        // gaming time
        timer.start();      // starts the timer
        timer.singleShot(TIME_FOR_REACTION, &ev, SLOT(quit())); // pause the game loop for TIME_FOR_REACTION ms and then quit ev
        timer.stop();       // stops the timer (needed for keypressevent)
        ev.exec();          // activate the event loop - needed for ESC
    }
    return true;
}






// protected
// keyEvent (Press)
void GameWindow::keyPressEvent(QKeyEvent *event){
    // if the timer is not active no key press events can take
    if(!timer.isActive()){
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


