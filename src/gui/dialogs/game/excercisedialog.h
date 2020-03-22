#ifndef EXCERCISEDIALOG_H
#define EXCERCISEDIALOG_H

#include <QDialog>

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

signals:
    void buttonPressed();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ExcerciseDialog *ui;

};

#endif // EXCERCISEDIALOG_H
