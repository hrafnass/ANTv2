#include "savedialog.h"
#include "ui_savedialog.h"
#include <iostream>

using namespace std;

SaveDialog::SaveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveDialog)
{
    ui->setupUi(this);
    connect(ui->pushButtonPrint, SIGNAL(clicked()), this, SLOT(printValues()));  // print the values in an html-file
}

SaveDialog::~SaveDialog()
{
    delete ui;
}

// public Methods
// Setter
void SaveDialog::SetSaving(Run *arg_r, QString* arg_name, QString* arg_fname, QString* arg_comm, QString* arg_birth){
    r = arg_r;
    name = arg_name;
    forename = arg_fname;
    comment = arg_comm;
    birthday = arg_birth;
}
