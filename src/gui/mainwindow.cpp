#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // blanks the cursor from
    measure.setCursor(Qt::BlankCursor);
    test.setCursor(Qt::BlankCursor);
    init = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

// init of the games
void MainWindow::InitGames(Run *arg_run, int arg_pass_number, unsigned int arg_nbr_of_runs){
    test.SetGame(arg_run,arg_pass_number,arg_nbr_of_runs);
    measure.SetGame(arg_run,arg_pass_number,arg_nbr_of_runs);
    init = true;
}

// open the About Game dialog
void MainWindow::on_actionAboutReactiongame_triggered()
{
    // AboutGamewindow is everytime in foreground
    about_game.setModal(true);
    about_game.show();
}

void MainWindow::on_startGamePushButton_clicked()
{
    if(!init){
        cout << "[***] Error: MainWindow InitGames wasn't set!!!"<<endl;
        return;
    }
    // saves the whole text input
    QString forename = ui->forenameLineEdit->text();
    QString name = ui->nameLineEdit->text();
    QString notice = ui->noticeTextEdit->toPlainText();
    QString birthday = ui->birthdayDateEdit->date().toString();
    // saves the birthday
    // check if forename, name or birthday is empty
    if(forename.isEmpty() || name.isEmpty() || birthday.isEmpty()){
        // open remind window
        reminder_dialog.setModal(true);
        reminder_dialog.show();
        return;
    }
    //test.Game();
    measure.SetMainWindowInput(forename, name, notice, birthday);
    measure.Game();
    // free labels
    ui->forenameLineEdit->setText("");
    ui->nameLineEdit->setText("");
    ui->noticeTextEdit->setText("");
}
