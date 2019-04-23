#include "aboutgamedialog.h"
#include "ui_aboutgamedialog.h"

AboutGameDialog::AboutGameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutGameDialog)
{
    ui->setupUi(this);
    // disables the maximization button in the About Game(Über Reaktionsspiel
    setFixedSize(width(), height());
}

AboutGameDialog::~AboutGameDialog()
{
    delete ui;
}
