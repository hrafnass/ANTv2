#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
// windows
#include "dialogs/main/aboutgamedialog.h"
#include "dialogs/main/reminder.h"
#include "game/game.h"
#include "src/background/run.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void InitGames(Run *arg_run);
private slots:
    // windows from the menu bar
    void on_actionAboutReactiongame_triggered();
    // game window started with button click
    void on_startGamePushButton_clicked();
private:
    // Windows UI
    Ui::MainWindow *ui;
    // gaming
    TestGame test;
    Measure measure;
    // ReminderDialog
    Reminder reminder_dialog;
    // aboutDialog
    AboutGameDialog about_game;

    Run *r;
    bool init;  // check if the game was init;
};

#endif // MAINWINDOW_H
