#include "savedialog.h"
#include "ui_savedialog.h"
#include <iostream>

using namespace std;

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

// if the save doesn't work - on_buttonBox_accept wasn't QDialogButtonBox::Save saving is false
void SaveDialog::setSaving(bool *save){
    saving = save;
}

void SaveDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton which = ui->buttonBox->standardButton(button);   // get the clicked button
    if(which == QDialogButtonBox::Save){
        cout << "SAVE" << endl;
        *saving = true;
    }else{
        *saving = false;
        cout << "Close" << endl;
    }
}
