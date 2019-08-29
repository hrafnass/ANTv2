#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    run.initRun(3);     // loaded the run with 3
    game.setCursor(Qt::BlankCursor);    // blanks the cursor from the game window
}

MainWindow::~MainWindow()
{
    delete ui;
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
    // saves the whole text input
    QString forename = ui->forenameLineEdit->text();
    QString name = ui->nameLineEdit->text();
    QString notice = ui->noticeTextEdit->toPlainText();
    QString birthday = ui->birthdayDateEdit->date().toString();
    // saves the birthday
    // check if forename, name or birthday is empty
    if(forename.isEmpty() || name.isEmpty() || birthday.isEmpty()){
        // open remind window
        Reminder reminder_dialog;
        reminder_dialog.setModal(true);
        reminder_dialog.exec();
        return;
    }
    run.newGame();          // start the settings for a new game
    cout << "start game" << endl;
    game.showFullScreen();  // open the window in fullscreen
    game.gameLoop(&run);    // start game loop

    // clear all measured values
    // calc.resetValues();
    // delete the whole input (forename, name, notice, birthday to Standard)
    ui->forenameLineEdit->setText("");
    ui->nameLineEdit->setText("");
    ui->noticeTextEdit->setText("");
}
