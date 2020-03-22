#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
// windows
#include "dialogs/main/aboutgamedialog.h"
#include "dialogs/main/reminder.h"
#include "gamewindow.h"
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
    // game function
    void gamingModes(bool);           // needed to start the game in exercise or measurement mode 

    // Windows UI
    Ui::MainWindow *ui;
    // gaming
    TestGame test;
    Measure measure;
    // ReminderDialog
    Reminder reminder_dialog;
    // aboutDialog
    AboutGameDialog about_game;

    Run run;
};

#endif // MAINWINDOW_H
