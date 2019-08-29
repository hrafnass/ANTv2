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
}




// protected
// keyEvent
void GameWindow::keyPressEvent(QKeyEvent *event){
    /* needed keys:
     *      ESC - quit the game
     *      left arrow and right arrow
     */
    // ESC
    if(event->key() == Qt::Key_Escape){
        cout << "close the gaming window" << endl;
        this->close();
        return;
    }

    if(event->key() == Qt::Key_Left){
        cout << "pressed left key" << endl;
    }

    if(event->key() == Qt::Key_Right){
        cout << "pressed right key" << endl;
    }

}
