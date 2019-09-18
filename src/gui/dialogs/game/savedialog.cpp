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
bool SaveDialog::setSaving(Saving *save, Run *run, QString name, QString  forename, QString comment, QString birthday){
    s = save;   // saves the address of saving in s
    s.setQFileDescriptor(name, forename);
    // saves all params in needed global variables
    r = run;
    com = comment;
    birth = birthday;
}


// protected: slots
// recieves the AcceptRole Buttonpress
void SaveDialog::accepted(){
    bool opened = s.openCSVFile();
    if(opened)
    {
        // saves all data
        cout << "save file" << endl;
        s.writeCSVFile(r, com, birth);
    }else{
        cout << "file couldn't open!!!" << endl;
    }
    s.closeCSVFile();   // close the descriptor
}

// recieves the RejectedRole Button Press
void SaveDialog::rejected(){ cout << "No File is saved!!!" << endl;}
