#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init = false;
    excercise.SetGameObjects(&measure, &test);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// init of the games
void MainWindow::InitGames(Run *arg_run){
    test.InitGame(arg_run,TRIALS_IN_RUN_TEST,NBR_OF_RUNS_TEST);
    measure.InitGame(arg_run,0,NBR_OF_RUNS_GAME);                // 0 loads the standard vector size
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
    QString ciphre = ui->ciphreLineEdit->text();
    QString notice = ui->noticeTextEdit->toPlainText();
    QString birthday = ui->birthdayLineEdit->text();
    // saves the birthday
    // check if ciphre or birthday is empty - no check if it is a real date
    if(ciphre.isEmpty() || birthday.isEmpty()){
        // open remind window
        reminder_dialog.setModal(true);
        reminder_dialog.show();
        return;
    }
    test.Game();
    measure.SetMainWindowInput(ciphre, notice, birthday);
    excercise.open();
    // free labels
    ui->ciphreLineEdit->setText("");
    ui->noticeTextEdit->setText("");
    ui->birthdayLineEdit->setText("");
}
