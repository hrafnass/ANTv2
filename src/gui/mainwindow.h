#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
// windows
#include "dialogs/main/aboutgamedialog.h"
#include "dialogs/main/reminder.h"
// moved from game window to main window
#include "dialogs/game/savedialog.h"
// excercise dialog
#include "dialogs/main/excercisedialog.h"

#include "gamewindow.h"
// classes for values and saving
// #include "../background/saving.h"
// #include "../background/calculation.h"
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
    void on_action_bung_triggered();

private:
    // game function
    void gamingModes(bool);           // needed to start the game in exercise or measurement mode 

    // Windows UI
    Ui::MainWindow *ui;
    // gaming
    GameWindow game;
    // SaveDialog
    SaveDialog save_dialog;
    // ReminderDialog
    Reminder reminder_dialog;
    // aboutDialog
    AboutGameDialog about_game;
    // excersice dialog
    ExcerciseDialog excercise_dialog;

    Run run;
    // saves all values
    // Saving save;
    // saves all values and calculations
    // Calculation calc;
};

#endif // MAINWINDOW_H
