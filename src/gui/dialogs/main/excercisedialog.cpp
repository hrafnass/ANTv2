#include "excercisedialog.h"
#include "ui_excercisedialog.h"

ExcerciseDialog::ExcerciseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExcerciseDialog)
{
    ui->setupUi(this);
}

ExcerciseDialog::~ExcerciseDialog()
{
    delete ui;
}

void ExcerciseDialog::on_buttonBox_accepted()
{

}

void ExcerciseDialog::on_buttonBox_rejected()
{

}
