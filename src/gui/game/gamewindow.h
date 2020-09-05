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
signals:
    void keyPressed(); // signal emittet in KeyPress
public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    // Game loop
    bool GameLoop(unsigned int arg_one_run/*size of one run - in test arg_pass_number == arg_one_run*/);    // loop for the game
    // setts the whole game
    void SetGame(Run *arg_run, int arg_pass_number, unsigned int arg_nbr_of_runs);
    // game setter
    void SetRun(Run *arg_run) { run = arg_run;}         // setter of the max. nbr of trials in the whole game
    void SetPassNbr(int arg_pass_number);
    void SetNbrOfRuns(unsigned int arg_nbr_of_runs);    // setter for the number of runs
    void SetTest(bool arg_test){ test = arg_test;}      // setter for test game check
    // Getter for GameWindow class
    Run* GetRun(){ return run;}
    bool GetRunLoop() { return run_game_loop;}          // is the game quitted by ESC
    unsigned int GetNbrOfRuns(){ return number_of_runs;}
protected:
    // Event funtions
    void keyPressEvent(QKeyEvent *);        // press key
    void keyReleaseEvent(QKeyEvent *);      // release keyf
private slots:
    /* quits the ev eventloop started in SleepGame (2.) so the next trial
     * could start immediatly (connected in constructor). If you need to whole
     * 2000ms for your reaction the second signal/slot connection in the
     * constructor reacts.*/
    void quit_eventloop() { ev.quit();}
private:
    // FOR GAMELOOP:
    bool StartCheckup(unsigned int arg_one_run, bool in_size);

    // GRAFIC SIZE AND CALCULATION FUNCTIONS
    // CALCULATION FUNCTIONS:
    int CmToPixelNbrX(double arg_width_in_cm);  // calculates the number of pixel on the user display (high definition, normal, ...) - X coord (width in pixel)
    int CmToPixelNbrY(double arg_height_in_cm); // -"-																				 - Y coord (height in pixel)
    // GRAFIC FUNCTIONS:
    void DeletePixmaps();               // deletes all pictures in all pixmaps
    void PaintStars(Trial *arg_trial);	// paint all stars (like clear screen)
    void PaintArrows(Trial *arg_trial);	// paint all arrows 		-"-
    void PaintPlus();                   // paints the plus img
    void PaintFeedback(string arg_feedback); // paints the correct or false image for the test game
    void SaveMeasuredValues(TrialComponents::DirectionMidArrow arg_direction);  // saves the components in trial
    // LABEL SETTINGS:
    void PaintListLabelsArrows(QList<QLabel *> arg_list,Trial *arg_trial,int arg_w,int arg_h); // paint a list of arrows
    void PaintStar(QLabel *arg_label, QString arg_img_name, int arg_w, int arg_h); // paint a star

    // TIME FUNCTIONS:
    /*
     * Parameter:   -arg_sleep_time(arg_sleep_time), arg_time(ResetWindow):
     *  The time the arrows shouldn't change
     *              -arrow(SleepGame, ResetWindow):
     *  check if it is the time between stars and arrows (1.)
     *  or the reaction time for the player(2.). true = (2.); false = (1.).
     *  The SleepGame-Algo. is different. For (1.) you shouldn't skip the stars
     *  for (2.) you should go immediatly to the next trial and don't wait until
     *  rest of the max reaction time is over (2000ms).
    */
    void SleepGame(int arg_sleep_time, bool arrow); // set the window to a sleep until a key was pressed or a max. time is over
    void ResetWindow(int arg_time, bool arrow);     // cleans the window after the sleep

    void SetSizeOfAllLabels();
    void IterateLabelList(QList<QLabel *> arg_list, int arg_w, int arg_h);

    // variables
    // needed vor the grafic surface
    Ui::GameWindow *ui;
    QEventLoop ev;                  // event loop - needed for keyRelease/PressEvent

    // timer
    QElapsedTimer timer;        // needed for time measurement
    QTimer quit;                // for the reaction

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
