#include "reminder.h"
#include "ui_reminder.h"

Reminder::Reminder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Reminder)
{
    ui->setupUi(this);
}

Reminder::~Reminder()
{
    delete ui;
}
