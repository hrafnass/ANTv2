/* ANTv2
 * This file is part of ANTv2.
 * 
 * ANTv2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * ANTv2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with ANTv2.  If not, see <https://www.gnu.org/licenses/>.
 */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
// windows
#include "dialogs/main/aboutgamedialog.h"   // about the used techs
#include "dialogs/main/instructions.h"      // whats the game about
#include "dialogs/main/reminder.h"          // is the input right
#include "dialogs/game/excercisedialog.h"   // excersice game dialog
#include "game/game.h"                      // the real game
#include "src/background/run.h"             // the trials in the background

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
    void on_actionAboutReactiongame_triggered();    // for the about ANT window
    void on_actionInstructions_triggered();
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
    // instruction dialog
    Instructions instruction_dialog;
    // excercise dialog
    ExcerciseDialog excercise;
    Run *r;
    bool init;  // check if the game was init;
};

#endif // MAINWINDOW_H
