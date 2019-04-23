#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <QWidget>
#include <QKeyEvent>
#include <QApplication>
#include <QtGui>

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
    // set label size
    void setLabelSize();

protected:
    void keyPressEvent(QKeyEvent *);

private:
    // private methods
    // methods to set the up and down labels - other_img take the pictures arround the mid image and mid_img is the mid label
    void setUpLables(QString other_img, QString mid_img);
    void setDownLables(QString other_img, QString mid_img);
    // choose which arrow position should loaded in setUp/DownLables
    void showImgArrow();         // show other and mid image on the right label - arrow images
    Ui::GameWindow *ui;
    // dialog between the three sessions
    SaveDialog save;    // save dialog, which is used when you press ESC
    // saves the run
    Run *run;


};

#endif // GAMEWINDOW_H
