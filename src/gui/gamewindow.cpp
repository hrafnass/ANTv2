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
