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

// if the save doesn't work - on_buttonBox_accept wasn't QDialogButtonBox::Save saving is false
void SaveDialog::setSaving(bool *save){
    saving = save;
}

// private slots
void SaveDialog::on_buttonBox_accepted()
{
    QAbstractButton clicked_button;   // saves the clicked button
    ui->buttonBox->clicked(&clicked_button);    // get the clicked button
    QDialogButtonBox::StandardButton button = ui->buttonBox->standardButton(&clicked_button);   // get the clicked button
    if(button == QDialogButtonBox::Save)
        *saving = true;
    else
        *saving = false;
}
