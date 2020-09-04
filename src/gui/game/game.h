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
