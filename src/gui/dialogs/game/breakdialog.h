#ifndef BREAKDIALOG_H
#define BREAKDIALOG_H

#include <QtWidgets/QDialog>

namespace Ui {
class BreakDialog;
}

class BreakDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BreakDialog(QWidget *parent = nullptr);
    ~BreakDialog();

private:
    Ui::BreakDialog *ui;
};

#endif // BREAKDIALOG_H
