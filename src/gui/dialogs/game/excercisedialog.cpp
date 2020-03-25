#include "excercisedialog.h"
#include "ui_excercisedialog.h"

using namespace std;

ExcerciseDialog::ExcerciseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExcerciseDialog)
{
    ui->setupUi(this);
    QPushButton *retry = ui->buttonBox->button(QDialogButtonBox::Retry);
    QPushButton *measure = ui->buttonBox->button(QDialogButtonBox::Ok);
    connect(retry, SIGNAL(clicked()), this, SLOT(on_buttonBox_clicked()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(on_buttonBox_accepted()));
}

ExcerciseDialog::~ExcerciseDialog()
{
    delete ui;
}
