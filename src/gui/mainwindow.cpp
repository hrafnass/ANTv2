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
    gamingModes(false);    // else the exercise is activated every time after on_action_bung_triggered() runed
    // save data
    save_dialog.setSaving(&run, name, forename, notice, birthday);
    save_dialog.setModal(true);
    save_dialog.exec();

}

// start in exercise mode Strg+U
void MainWindow::on_action_bung_triggered() {
    gamingModes(true);
    // ask the user for a new excercise
    excercise_dialog.setModal(true);
    excercise_dialog.exec();
}

// game function
void MainWindow::gamingModes(bool mode){
    game.setExercise(mode);
    run.newGame();          // start the settings for a new game
    game.showFullScreen();  // open the window in fullscreen
    game.gameLoop();        // start game loop
}
