#include "breakdialog.h"
#include "ui_breakdialog.h"

BreakDialog::BreakDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BreakDialog)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()),this, SLOT(execEventLoop()));
}

BreakDialog::~BreakDialog()
{
    delete ui;
}
