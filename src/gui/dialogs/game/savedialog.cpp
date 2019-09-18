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

// setter für Saving
bool SaveDialog::setSaving(Saving *save, QString name, QString  forename){
    s = save;   // saves the address of saving in s
    s.setQFileDescriptor(name, forename);
}


// protected: slots
// recieves the AcceptRole Buttonpress
void SaveDialog::accepted(){
    
}


/*
    // writes the data in a csv file
    if(save.openCSVFile(name, forename))
    {
        save.writeCSVFile(run, comment, birthday);
    }else {
        return false;
    }
    save.closeCSVFile();    // close file
    return true;
*/
