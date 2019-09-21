#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    run.initRun(3);     // loaded the run with 3
    game.setRun(&run);  // give run to GameWindow
    game.setCursor(Qt::BlankCursor);    // blanks the cursor from the game window
}

MainWindow::~MainWindow()
{
    delete ui;
}

// open the About Game dialog
void MainWindow::on_actionAboutReactiongame_triggered()
{
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
        reminder_dialog.setModal(true);
        reminder_dialog.exec();
        return;
    }
    // free labels
    ui->forenameLineEdit->setText("");
    ui->nameLineEdit->setText("");
    ui->noticeTextEdit->setText("");
    // game
    run.newGame();          // start the settings for a new game
    game.showFullScreen();  // open the window in fullscreen
    game.gameLoop();        // start game loop
    // save data
    // save_dialog.setSaving(&save, &run, name, forename, notice, birthday);   // save all infos for the save dialog
    save_dialog.setModal(true);
    save_dialog.exec();

}
