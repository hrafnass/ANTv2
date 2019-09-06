#ifndef SAVEDIALOG_H
#define SAVEDIALOG_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QAbstractButton>

namespace Ui {
class SaveDialog;
}

class SaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveDialog(QWidget *parent = nullptr);
    ~SaveDialog();
    void setSaving(bool*);    // set the saving
private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::SaveDialog *ui;
    bool saving; // check if the dialog game should save
};

#endif // SAVEDIALOG_H
