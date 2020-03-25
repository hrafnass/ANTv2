#ifndef GAME_H
#define GAME_H

#include <QObject>

#include "gamewindow.h"
#include "src/gui/dialogs/game/breakdialog.h"

// The Real Game
class Measure {
public:
    Measure(){game.setCursor(Qt::BlankCursor);}
    //~Measure() {}
    bool Game();
    // setter for the input
    void SetMainWindowInput(QString arg_forename, QString arg_name, QString arg_notice, QString arg_birthday);
    void InitGame(Run *arg_run, int arg_pass_number, unsigned int arg_nbr_of_runs){ game.SetGame(arg_run,arg_pass_number,arg_nbr_of_runs);}
private:
    // measurement dialogs - and game window
    BreakDialog pause;
    GameWindow game;
    //SaveDialog save;
    // input
    QString forename;
    QString name;
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
    ExcerciseDialog* GetExcerciseDialog() { return &excercise;}
protected:
    void ResetWindow(int arg_time); // override to show smiles
private:
    ExcerciseDialog excercise;
    GameWindow game;
};

#endif // GAME_H
