#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    run.initRun(3);     // loaded the run with 3
    game.setRun(&run);  // give run to gamewindow
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
    // when the game should save s is true
    bool s = false;
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
    }else {
        run.newGame();          // start the settings for a new game
        cout << "start game" << endl;
        game.showFullScreen();  // open the window in fullscreen
        game.startSettings(&s); // sets the size of all labels
        game.gameLoop();        // start game loop
        s = true;               // wenn the game finished, all measured values can be saved
    }
    // save all calculated values
    if(s){
        // reset the calculations
        calc.resetValues();
        // save the values
        if(!save.openCSVFile(forename, name))    // if the file descriptor doesn't open
            return;
        save.writeCSVFile(&run, &calc, notice, birthday);
        save.closeCSVFile();
    }
    // clear all measured values
    // calc.resetValues();
    // delete the whole input (forename, name, notice, birthday to Standard)
    ui->forenameLineEdit->setText("");
    ui->nameLineEdit->setText("");
    ui->noticeTextEdit->setText("");
}
