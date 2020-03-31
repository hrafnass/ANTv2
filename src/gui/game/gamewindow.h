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
    // setts the whole game
    void SetGame(Run *arg_run, int arg_pass_number, unsigned int arg_nbr_of_runs);
    // game setter
    void SetRun(Run *arg_run) { run = arg_run;}
    // setter of the max. nbr of trials in the whole game
    void SetPassNbr(int arg_pass_number);
    // setter for the number of runs
    void SetNbrOfRuns(unsigned int arg_nbr_of_runs);
    // setter for test game check
    void SetTest(bool arg_test){ test = arg_test;}
    // Getter for GameWindow class
    Run* GetRun(){ return run;}
    unsigned int GetNbrOfRuns(){ return number_of_runs;}
protected:
    // Event funtions
    void keyPressEvent(QKeyEvent *);        // press key
    void keyReleaseEvent(QKeyEvent *);      // release keyf
private:
    void SaveMeasuredValues(TrialComponents::DirectionMidArrow arg_direction);  // saves the components in trial
    // calculation functions
    int CmToPixelNbrX(double arg_width_in_cm);  // calculates the number of pixel on the user display (high definition, normal, ...) - X coord (width in pixel)
    int CmToPixelNbrY(double arg_height_in_cm); // -"-																				 - Y coord (height in pixel)

    // painting functions
    void DeletePixmaps();		// deletes all pictures in all pixmaps
    void PaintStars(Trial *arg_trial);	// paint all stars (like clear screen)
    void PaintArrows(Trial *arg_trial);	// paint all arrows 		-"-
    void PaintPlus();           // paints the plus img
    void PaintFeedback(string arg_feedback); // paints the correct or false image for the test game

    // functions for label settings
    void PaintListLabelsArrows(QList<QLabel *> arg_list,Trial *arg_trial,int arg_w,int arg_h); // paint a list of arrows
    void PaintStar(QLabel *arg_label, QString arg_img_name, int arg_w, int arg_h); // paint a star

    // function which cleans the window and set it to sleep
    void SleepGame(int arg_sleep_time);
    void ResetWindow(int arg_time);

    void SetSizeOfAllLabels();
    void IterateLabelList(QList<QLabel *> arg_list, int arg_w, int arg_h);

    // variables
    // needed vor the grafic surface
    Ui::GameWindow *ui;
    QEventLoop ev;                  // event loop - needed for keyRelease/PressEvent

    // needed for time measurement
    QElapsedTimer timer;

    // label lists
    QList<QLabel *> up_arrows;
    QList<QLabel *> down_arrows;

    // The Run for the Game
    Run *run = nullptr;
    unsigned int number_of_runs; // saves how many runs are used - if it isn't set or < 1 standard is 2
    bool run_game_loop; // for ESC - quit the game loop
    // check if the game is a test game
    bool test;
};

#endif // GAMEWINDOW_H
