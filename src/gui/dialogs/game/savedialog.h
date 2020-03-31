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
private slots:
    void acceptSaveDialog(){ this->done(QDialog::Accepted);}
private:
    // Variables
    Ui::SaveDialog *ui;
};

#endif // SAVEDIALOG_H
