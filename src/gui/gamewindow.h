#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

// DIRECTIONS
#define RIGHT 	1             // for the measure of the pressed keys: RIGHT = 1
#define LEFT 	0             //              -"-                     LEFT  = 0

/*
 * Explanation of paintPlus:
 * Problem: If a star and a plus is printed the plus jumps up or down, but the plus doesn't jump if the star is located
 * up and down.
 * Why? If the pictures have different heights the spacer moves the mid label (Centreline) up or down. So the MidAbove
 * and MidBelow label need the same size (setFixedHeight).
 * There are 2 possible solutions:
 *      1. All heights have to be the same, so the plus can't move up or down
 *      2. You set the labels over and und the plus at the same value (STAR_Y, because a star is shown at the same time.
*/

// PICTURE LENGTHS IN CM
#define STAR_X 	1
#define ARROW_X 2
#define PLUS_X  1
#define BAR_X   2
// PICTURE WIDTHS IN CM
#define STAR_Y  1
#define ARROW_Y 1
#define PLUS_Y  1
#define BAR_Y   1

// SPACER DISTANCE IN CM
#define DISTANCE_ARROW_PLUS_Y 2     // its the fixed distance of a spacer - we use 2.54  at the moment
#define DISTANCE_ARROW_PLUS_X 2     // its the fixed distance of a spacer - we use 2.54  at the moment

// 2.54 cm = 1 Inch
#define INCH_IN_CM 2.54

// PICTURE NAMES
#define STAR_NAME ":/ressources/images/star.svg"
#define PLUS_NAME ":/ressources/images/plus.svg"

// TRAININGS MODE TEXTS
#define CORRECT ":/ressources/images/right.svg"
#define WRONG ":/ressources/images/false.svg"


// TIMES
// waiting times in ther game
#define TIME_BETWEEN_ARROWS 1000    // in ms
#define TIME_FOR_REACTION   2000    // in ms

#include <QtCore/QElapsedTimer>
#include <QtCore/QTimer>
#include <QtCore/QRegularExpression>

#include <QtGui/QKeyEvent>
#include <QtGui/QCursor>

#include <QtWidgets/QWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>

// Game Dialogs
// #include "src/gui/dialogs/game/savedialog.h"
#include "src/gui/dialogs/game/breakdialog.h"
// background functions
#include "../background/run.h"
#include "../background/saving.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    // game loop
    bool gameLoop();      // gaming loop
    // bool gameResults(QString, QString, QString, QString);   // saves and calculates all mvalues
    // add run
    void setRun(Run *r) { run = r;}
    // game or exercise - only needed for Strg+H in mainwindow
    void setExercise(bool exercise) { train = exercise;}

protected:
	// Events
    void keyPressEvent(QKeyEvent *);        // press key
    void keyReleaseEvent(QKeyEvent *);      // release key

private:
	// functions
	// size calculation
    int cmToPixelNbrX(double);		// calculates the number of pixel on the user display (high definition, normal, ...) - X coord (width in pixel)
    int cmToPixelNbrY(double);		// -"-																				 - Y coord (height in pixel)
    
    // screen manipulation (paint, delete, ...)
    void deletePixmaps();		// deletes all pictures in all pixmaps
    void paintStars(Trial *);	// paint all stars (like clear screen)
    void paintArrows(Trial *);	// paint all arrows 		-"-
    void paintPlus();           // paints the plus img
    // dialog painting
    void paintBreakDialog();    // paints the BreakDialog

    // functions for label settings
    void paintListLabelsArrows(QList<QLabel *>,QString,int,int);    // paint a list of "other arrows"
    void paintStar(QLabel *, QString, int, int);                    // paint a star

    // trainings functions
    void training();    // check if the exercise mode is active and paint the right input for the labels

	// variables
    // needed vor the grafic surface
    Ui::GameWindow *ui;
    QEventLoop ev;                  // event loop - needed for keyRelease/PressEvent

    // needed for time measurement
    QElapsedTimer timer;
    Run *run;

    // main game loop
    bool game;
    // setting variable to check if the game window only was opened by void on_action_bung_triggered() (mainwindow)
    // needed for training
    bool train;
};

#endif // GAMEWINDOW_H
