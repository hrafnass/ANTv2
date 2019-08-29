#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#define RIGHT 1             // for the measure of the pressed keys: RIGHT = 1
#define LEFT 0              //              -"-                     LEFT  = 0

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

	// variables
    // needed vor the grafic surface
    Ui::GameWindow *ui;
    QEventLoop ev;                  // event loop - needed for keyRelease/PressEvent

    // needed for time measurement
    QElapsedTimer timer;
};

#endif // GAMEWINDOW_H
