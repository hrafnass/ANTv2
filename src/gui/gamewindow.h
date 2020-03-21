#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "game_headers.h"

namespace Ui {
class GameWindow;
}

// basic class for the measurement and the test

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    // Game loop
    bool GameLoop(int arg_one_run/*size of one run - in test arg_pass_number == arg_one_run*/);    // loop for the game
    // setter for run
    void SetRun(Run *arg_run) { run = arg_run;}
    // setter of the max. nbr of trials in the whole game
    void SetPassNbr(int arg_pass_number);

protected:
    // Event funtions
    void keyPressEvent(QKeyEvent *);        // press key
    void keyReleaseEvent(QKeyEvent *);      // release key
    void SaveMeasuredValues(TrialComponents::DirectionMidArrow arg_direction);  // saves the components in trial

    // calculation functions
    int CmToPixelNbrX(double arg_width_in_cm);  // calculates the number of pixel on the user display (high definition, normal, ...) - X coord (width in pixel)
    int CmToPixelNbrY(double arg_height_in_cm); // -"-																				 - Y coord (height in pixel)

    // painting functions
    void DeletePixmaps();		// deletes all pictures in all pixmaps
    void paintStars(Trial *);	// paint all stars (like clear screen)
    void paintArrows(Trial *);	// paint all arrows 		-"-
    void PaintPlus();           // paints the plus img

    // functions for label settings
    void paintListLabelsArrows(QList<QLabel *>,QString,int,int);    // paint a list of "other arrows"
    void paintStar(QLabel *, QString, int, int);                    // paint a star

    // function which cleans the window and set it to sleep
    void SleepGame(int arg_sleep_time);
    void ResetWindow(int arg_time);

    // variables
    // needed vor the grafic surface
    Ui::GameWindow *ui;
    QEventLoop ev;                  // event loop - needed for keyRelease/PressEvent

    // needed for time measurement
    QElapsedTimer timer;

    // The Run for the Game
    Run *run = nullptr;
};

// The Real Game
class Measure : public GameWindow{
public:
    void BreakDialog();
    void PrintDialog();
protected:
    void CheckAndLoadDialogs(); // muss dann überschrieben werden
};

// The Test Game
class Test : public GameWindow {
public:
    void StopTestDialog();

protected:
    void CheckAndLoadDialogs(); // muss dann überschrieben werden
    void ResetWindow(int arg_time); // override to show smiles
};

#endif // GAMEWINDOW_H
