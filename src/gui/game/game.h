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


#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QtWidgets>

#include "gamewindow.h"
#include "src/gui/dialogs/game/breakdialog.h"
#include "src/gui/dialogs/game/savedialog.h"

// The Real Game
class Measure : public QObject{
    Q_OBJECT

public:
    Measure();
    //~Measure() {}
    bool Game();
    // setter for the input
    void SetMainWindowInput(QString arg_ciphre, QString arg_notice, QString arg_birthday);
    void InitGame(Run *arg_run, int arg_pass_number, unsigned int arg_nbr_of_runs){ game.SetGame(arg_run,arg_pass_number,arg_nbr_of_runs);}

private slots:
    void printHTML();
private:
    // game loop pause
    int PauseWindow();
    // save files
    bool SaveCSV();
    bool SaveHTML();
    // measurement dialogs - and game window
    BreakDialog pause;
    SaveDialog save;
    GameWindow game;
    // files
    CSVDocument csv;
    JSDocument js;
    // run
    Run *run = nullptr;
    // input
    QString ciphre;
    QString notice;
    QString birthday;
};

// The Test Game
class TestGame : public QObject
{
    Q_OBJECT

public:
    TestGame() { game.setCursor(Qt::BlankCursor);}     // construcotr
    void InitGame(Run *arg_run, int arg_pass_number, unsigned int arg_nbr_of_runs){ game.SetGame(arg_run,arg_pass_number,arg_nbr_of_runs);}
    bool Game();    // game
    // getter for ExcerciseDialog
protected:
    void ResetWindow(int arg_time); // override to show smiles

private:
    GameWindow game;
};

#endif // GAME_H
