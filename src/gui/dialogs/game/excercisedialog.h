#ifndef EXCERCISEDIALOG_H
#define EXCERCISEDIALOG_H

#include <QDialog>
#include <QtWidgets>

#include "src/gui/game/game.h"

#include <iostream>

namespace Ui {
class ExcerciseDialog;
}

class ExcerciseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExcerciseDialog(QWidget *parent = nullptr);
    ~ExcerciseDialog();

    void SetGameObjects(Measure *arg_m, TestGame *arg_t){ m = arg_m; t=arg_t;}

public slots:
    void measure();
    void testing();

private:
    Ui::ExcerciseDialog *ui;

    Measure *m;
    TestGame *t;
};

#endif // EXCERCISEDIALOG_H
