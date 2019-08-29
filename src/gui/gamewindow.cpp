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

}
