#ifndef ABOUTGAMEDIALOG_H
#define ABOUTGAMEDIALOG_H

#include <QDialog>

namespace Ui {
class AboutGameDialog;
}

class AboutGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutGameDialog(QWidget *parent = 0);
    ~AboutGameDialog();

private:
    Ui::AboutGameDialog *ui;
};

#endif // ABOUTGAMEDIALOG_H
