#ifndef GAME_H
#define GAME_H

#include "gamewindow.h"

// The Real Game
class Measure {
public:
    //Measure(){}
    //~Measure() {}
    bool Game();
    // setter for the input
    void SetMainWindowInput(QString arg_forename, QString arg_name, QString arg_notice, QString arg_birthday);
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
class TestGame {
public:
    TestGame();     // construcotr
    bool Game();    // game
    // SLOT
    void on_action_excercise_triggered();
protected:
    void ResetWindow(int arg_time); // override to show smiles
private:
    ExcerciseDialog excercise;
    GameWindow game;
};

#endif // GAME_H
