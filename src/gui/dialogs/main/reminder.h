#ifndef REMINDER_H
#define REMINDER_H

#include <QtWidgets/QDialog>
namespace Ui {
class Reminder;
}

class Reminder : public QDialog
{
    Q_OBJECT

public:
    explicit Reminder(QWidget *parent = nullptr);
    ~Reminder();

private:
    Ui::Reminder *ui;
};

#endif // REMINDER_H
