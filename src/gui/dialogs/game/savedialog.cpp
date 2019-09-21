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
bool SaveDialog::setSaving(Run *run, QString name, QString  forename, QString comment, QString birthday){
    // catch all needed params
    r = run;
    com = comment;
    birth = birthday;
    s.setQFileDescriptor(name, forename);
}

// private slots:

void SaveDialog::on_buttonBox_accepted()
{
    setValues();                        // get the needed values
    bool opened = s.openCSVFile();      // try to opens a file
    if(opened)
    {
        // saves all data
        cout << "[*] Save file!!!" << endl;
        s.writeCSVFile(r, com, birth);
        s.closeCSVFile();   // close the descriptor
    }else{
        cout << "[*] Couldn't open file!!!" << endl;
    }
    this->close(); // close the window
    return;
}

void SaveDialog::on_buttonBox_rejected()
{
    cout << "[*] No File is saved!!!" << endl;
    this->close();
    return;
}

// private:
void SaveDialog::setValues(){
    // delete and calcs the new values
    c.resetValues();
    c.calcValues(r);
}
