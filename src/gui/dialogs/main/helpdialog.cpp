#include "helpdialog.h"
#include "ui_helpdialog.h"

HelpDialog::HelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);
    // disables maximization button in the help dialog
    setFixedSize(width(), height());
}

HelpDialog::~HelpDialog()
{
    delete ui;
}
