#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H


// DIRECTIONS
#define RIGHT 	1             // for the measure of the pressed keys: RIGHT = 1
#define LEFT 	0             //              -"-                     LEFT  = 0

// PICTURE LENGTHS IN CM
#define STAR_X 	1
#define ARROW_X 2.54
#define PLUS_X  1.6
#define BAR_X   2.54
// PICTURE WIDTHS IN CM
#define STAR_Y  1
#define ARROW_Y 0.6
#define PLUS_Y  1.6
#define BAR_Y   0.6


// TIMES
// waiting times in ther game
#define TIME_BETWEEN_ARROWS 1000    // in ms
#define TIME_FOR_REACTION   2000    // in ms

#include <QtCore/QElapsedTimer>
#include <QtCore/QTimer>

#include <QtGui/QKeyEvent>
#include <QtGui/QCursor>

#include <QtWidgets/QWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>

// Game Dialogs
#include "src/gui/dialogs/game/savedialog.h"
#include "src/gui/dialogs/game/breakdialog.h"
// background functions
#include "../background/run.h"

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
    bool gameLoop(Run *r);      // gaming loop    

protected:
	// Events
    void keyPressEvent(QKeyEvent *);        // press key
    void keyReleaseEvent(QKeyEvent *);      // release key

private:
	// functions
	// size calculation
    int cmToPixelNbrX(int);		// calculates the number of pixel on the user display (high definition, normal, ...) - X coord (width in pixel)
    int cmToPixelNbrY(int);		// -"-																				 - Y coord (height in pixel)
    
    // screen manipulation (paint, delete, ...)
    void deletePixmaps();		// deletes all pictures in all pixmaps
    void paintStars();			// paint all stars (like clear screen)
    void paintArrows(Trial *);	// paint all arrows 		-"-

    // list functions
    void paint(QList<QLabel *>,QString);

	// variables
    // needed vor the grafic surface
    Ui::GameWindow *ui;
    QEventLoop ev;                  // event loop - needed for keyRelease/PressEvent

    // needed for time measurement
    QElapsedTimer timer;
};

#endif // GAMEWINDOW_H
