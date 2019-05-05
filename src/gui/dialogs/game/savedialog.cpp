#include "savedialog.h"
#include "ui_savedialog.h"

SaveDialog::SaveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveDialog)
{
    ui->setupUi(this);
}

SaveDialog::~SaveDialog()
{
    delete ui;
}

// save/not save the run
void SaveDialog::on_buttonBox_accepted(){

}
