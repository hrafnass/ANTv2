#ifndef SAVEDIALOG_H
#define SAVEDIALOG_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QAbstractButton>

// background functions
#include "../../../background/run.h"
// classes for values and saving
#include "../../../background/saving.h"
#include "../../../background/calculation.h"

namespace Ui {
class SaveDialog;
}

class SaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveDialog(QWidget *parent = nullptr);
    ~SaveDialog();
    bool setSaving(Run *, QString, QString, QString, QString);    // to init the save and calculation of all values

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    // Functions
    void setValues();

    // Variables
    Ui::SaveDialog *ui;
    // calculation and saving
    Saving s;           // save all data
    Calculation c;      // calculation
    // needed for startSaving
    Run *r;
    QString com;
    QString birth;
};

#endif // SAVEDIALOG_H
