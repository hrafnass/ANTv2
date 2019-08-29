#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
// windows
#include "dialogs/main/aboutgamedialog.h"
#include "dialogs/main/reminder.h"
#include "gamewindow.h"
// classes for values and saving
#include "../background/saving.h"
#include "../background/calculation.h"
#include "../background/run.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // windows from the menu bar
    void on_actionAboutReactiongame_triggered();
    // game window started with button click
    void on_startGamePushButton_clicked();
private:
    // Windows
    Ui::MainWindow *ui;
    // gaming
    //GameWindow game;
    Run run;
    // saves all values
    Saving save;
    // saves all values and calculations
    Calculation calc;
};

#endif // MAINWINDOW_H
