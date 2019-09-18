#ifndef SAVEDIALOG_H
#define SAVEDIALOG_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QAbstractButton>

// background
#include "../background/saving.h"

namespace Ui {
class SaveDialog;
}

class SaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveDialog(QWidget *parent = nullptr);
    ~SaveDialog();
    bool setSaving(Saving *save, QString name, QString  forename, QString  notice, QString  birthday);
private slots:
    void accepted();
    void rejected();

private:
    Ui::SaveDialog *ui;
    Saving *s;          // save all data
};

#endif // SAVEDIALOG_H
