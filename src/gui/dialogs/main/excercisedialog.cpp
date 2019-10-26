#include "excercisedialog.h"
#include "ui_excercisedialog.h"

using namespace std;

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
    cout << "new excercise" << endl;
}

// no button was pushed
void ExcerciseDialog::on_buttonBox_rejected() { cout << "finished excercise!!!" << endl; }
