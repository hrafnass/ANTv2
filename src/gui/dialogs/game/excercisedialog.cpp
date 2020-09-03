#include "excercisedialog.h"
#include "ui_excercisedialog.h"

using namespace std;

ExcerciseDialog::ExcerciseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExcerciseDialog)
{
    ui->setupUi(this);
    connect(ui->pushButtonMeasure, SIGNAL(clicked()), this, SLOT(measure()));
    connect(ui->pushButtonRetry, SIGNAL(clicked()), this, SLOT(testing()));
}

ExcerciseDialog::~ExcerciseDialog()
{
    delete ui;
}

void ExcerciseDialog::measure() {
    std::cout << "measure - slot!!!"<<std::endl;
    m->Game();
    // this->open();
}

void ExcerciseDialog::testing() {
    std::cout << "testing - slot!!!"<<std::endl;
    t->Game();
    this->open();
}
