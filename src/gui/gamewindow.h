#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#define STAR true
#define ARROW false

#include <QWidget>
#include <QKeyEvent>
#include <QApplication>
#include <QtGui>
#include <QLabel>
#include <QTime>

// Game Dialogs
#include "src/gui/dialogs/game/savedialog.h"
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
    // set the Run
    void setRun(Run *run);
    // set label size at the start
    void startSettings();
    void gameLoop();                        // THE GAME

protected:
    void keyPressEvent(QKeyEvent *);

private:   
    // private methods
    void delay(int);                        // set a delay in gameLoop
    // functions to create all values for the images and load them
    int pixel(double, char);                // calculates the amount of pixels for x or y coordinates (for x char x_or_y == 'x')
    void setLabelSize(QLabel *, int, int);  // set the size of an label
    // methods to set the up and down labels - other_img take the pictures arround the mid image and mid_img is the mid label
    void setUpLables(QString other_img, QString mid_img, int arrow_width, int height);
    void setDownLables(QString other_img, QString mid_img, int arrow_width, int height);
    void clearScreen();     // removes input from all labels (load a white pixmap - look if there is a better method)
    // choose which arrow position should loaded in setUp/DownLables
    void imgLoader(bool);                // clear the screen and load the arrow or the star image
    void showImgArrow(Trial);            // show other and mid image on the right label - arrow images
    void showImgStars(Trial);            // shows all stars
    Ui::GameWindow *ui;
    // dialog between the three sessions
    SaveDialog save;    // save dialog, which is used when you press ESC
    // saves the run
    Run *run;
    // saves the image names
    const QString star_img = ":/ressources/images/star.svg";
    const QString plus_img = ":/ressources/images/plus.svg";
};

#endif // GAMEWINDOW_H
