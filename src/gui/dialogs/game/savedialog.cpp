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
    s->setQFileDescriptor(name, forename);
    // saves all params in needed global variables
    r = run;
    com = comment;
    birth = birthday;
}


// protected: slots
// recieves the AcceptRole Buttonpress
void SaveDialog::accept(){
    bool opened = s->openCSVFile();
    cout << "2.1 ";
    if(opened)
    {
        // saves all data
        cout << "save file" << endl;
        s->writeCSVFile(r, com, birth);
        s->closeCSVFile();   // close the descriptor
        cout << "2.2 ";
    }else{
        cout << "file couldn't open!!!" << endl;
    }
    cout << "2.3 ";
    this->close(); // close the window
    cout << "2.4 " << endl;
    return;
}

// recieves the RejectedRole Button Press
/*void SaveDialog::reject(){
    cout << "No File is saved!!!" << endl;
    this->close();
    return;
}*/

