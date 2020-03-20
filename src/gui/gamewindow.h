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

protected:
    // Event funtions
    void keyPressEvent(QKeyEvent *);        // press key
    void keyReleaseEvent(QKeyEvent *);      // release key

    // calculation functions
    int cmToPixelNbrX(double);		// calculates the number of pixel on the user display (high definition, normal, ...) - X coord (width in pixel)
    int cmToPixelNbrY(double);		// -"-																				 - Y coord (height in pixel)

    // painting functions
    void deletePixmaps();		// deletes all pictures in all pixmaps
    void paintStars(Trial *);	// paint all stars (like clear screen)
    void paintArrows(Trial *);	// paint all arrows 		-"-
    void paintPlus();           // paints the plus img

    // functions for label settings
    void paintListLabelsArrows(QList<QLabel *>,QString,int,int);    // paint a list of "other arrows"
    void paintStar(QLabel *, QString, int, int);                    // paint a star

    // variables
    // needed vor the grafic surface
    Ui::GameWindow *ui;
    QEventLoop ev;                  // event loop - needed for keyRelease/PressEvent

    // needed for time measurement
    QElapsedTimer timer;
};

// The Real Game
class Measure : public GameWindow{
public:

private:
};

// The Test Game
class Test : public GameWindow {
public:

private:
};

#endif // GAMEWINDOW_H
