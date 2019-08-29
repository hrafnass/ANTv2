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
    while(r->readRun()){
        // clear screen

        // paint svgs (stars)

        QTimer::singleShot(TIME_BETWEEN_ARROWS, &ev, SLOT(quit())); // stops event loop for timer restart


        // clear screen (stars)

        // paint arrows
        // gaming time
        timer.restart();        // restarts the timer
        ev.exec();              // starts the event loop
        QTimer::singleShot(TIME_FOR_REACTION, &ev, SLOT(quit())); // pause the game loop for TIME_FOR_REACTION ms and then quit ev
        ev.exec();          // activate the event loop - needed for ESC
    }
    this->close();
    return true;
}






// protected
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


