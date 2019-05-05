#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    run.initRun(2);     // loaded the run with 3
    game.setRun(&run);  // give run to gamewindow
}

MainWindow::~MainWindow()
{
    delete ui;
}

// open the Helpwindow dialog
void MainWindow::on_actionHelp_triggered()
{
    HelpDialog help_dialog;
    // Helpwindow is everytime in foreground
    help_dialog.setModal(true);
    help_dialog.exec();
}

// open the About Game dialog
void MainWindow::on_actionAboutReactiongame_triggered()
{
    AboutGameDialog about_game;
    // AboutGamewindow is everytime in foreground
    about_game.setModal(true);
    about_game.exec();
}

void MainWindow::on_startGamePushButton_clicked()
{
    // when the game should save s is true
    bool s = false;
    // saves the whole text input
    QString forename = ui->forenameLineEdit->text();
    QString name = ui->nameLineEdit->text();
    QString notice = ui->noticeTextEdit->toPlainText();
    // saves the birthday
    // check if forename or name is empty
    if(forename.isEmpty() || name.isEmpty()){
        // open remind window
        Reminder reminder_dialog;
        reminder_dialog.setModal(true);
        reminder_dialog.exec();
        ui->birthdayLabel->setPixmap(QPixmap(QString::fromUtf8(":/cross_klein.png")));
        return;
    }else {
        run.newGame();          // start the settings for a new game
        game.showFullScreen();  // open the window in fullscreen
        game.startSettings(&s);   // sets the size of all labels
        game.gameLoop();        // start game loop
    }
    // save all calculated values
    if(s){
        save.openCSVFile(forename, name);
        save.writeCSVFile(&run, &calc, notice);
        save.closeCSVFile();
    }
    // clear all measured values
    calc.resetValues();
    // delete the whole input (forename, name, notice, birthday to Standard)
    ui->forenameLineEdit->setText("");
    ui->nameLineEdit->setText("");
    ui->noticeTextEdit->setText("");
}
