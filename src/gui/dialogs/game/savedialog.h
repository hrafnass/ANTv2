#ifndef SAVEDIALOG_H
#define SAVEDIALOG_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QAbstractButton>

// background functions
#include "src/background/run.h"
// classes for values and saving
#include "src/background/saving.h"
#include "src/background/calculation.h"

namespace Ui {
class SaveDialog;
}

class SaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveDialog(QWidget *parent = nullptr);
    ~SaveDialog();
    // Setter for all needed values
    void SetSaving(Run *arg_r, QString* arg_name, QString* arg_fname, QString* arg_comm, QString* arg_birth);    // to init the save and calculation of all values

private slots:
    void printValues();

private:
    // Variables
    Ui::SaveDialog *ui;
    // all needed values
    Run *r;
    QString *name;
    QString *forename;
    QString *comment;
    QString *birthday;
};

#endif // SAVEDIALOG_H
