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
void SaveDialog::SetSaving(Run *arg_r, QString* arg_name, QString* arg_fname){
    r = arg_r;
    name = arg_name;
    forename = arg_fname;
}


// private slots
void SaveDialog::printValues(){
    HTMLDocument html;
    Calculation calc;
    bool ret = false;

    ret = html.CreateHTMLFile(name, forename);
    if(ret == false){
        cout << "[***] Error: Error in printValues(CreateHTMLFile) - private Slot SaveDialog"<<endl;
        return;
    }
    ret = html.WriteHTMLFile(&calc);
    if(ret == false){
        cout << "[***] Error: Error in printValues(WriteHTMLFile) - private Slot SaveDialog"<<endl;
        return;
    }
}
