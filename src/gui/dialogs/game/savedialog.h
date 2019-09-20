#ifndef SAVEDIALOG_H
#define SAVEDIALOG_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QAbstractButton>

// background functions
#include "../../../background/run.h"
#include "../../../background/saving.h"

namespace Ui {
class SaveDialog;
}

class SaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveDialog(QWidget *parent = nullptr);
    ~SaveDialog();
    bool setSaving(Saving *save, Run *run, QString name, QString  forename, QString comment, QString birthday);
private slots:
    void accept();
    //void reject();

private:
    Ui::SaveDialog *ui;
    Saving *s;          // save all data
    // needed for setSaving
    Run *r;
    QString com;
    QString birth;
};

#endif // SAVEDIALOG_H
