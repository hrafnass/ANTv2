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
private slots:

private:
    Ui::SaveDialog *ui;
};

#endif // SAVEDIALOG_H
