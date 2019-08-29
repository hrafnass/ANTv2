#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

// #define STAR true
// #define ARROW false
#define RIGHT 1             // for the measure of the pressed keys: RIGHT = 1
#define LEFT 0              //              -"-                     LEFT  = 0

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

protected:
    void keyPressEvent(QKeyEvent *);        // get the key events

private:
    Ui::GameWindow *ui;
};

#endif // GAMEWINDOW_H
