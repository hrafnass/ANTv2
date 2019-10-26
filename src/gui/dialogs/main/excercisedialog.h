#ifndef EXCERCISEDIALOG_H
#define EXCERCISEDIALOG_H

#include <QDialog>

namespace Ui {
class ExcerciseDialog;
}

class ExcerciseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExcerciseDialog(QWidget *parent = nullptr);
    ~ExcerciseDialog();

private:
    Ui::ExcerciseDialog *ui;
};

#endif // EXCERCISEDIALOG_H
