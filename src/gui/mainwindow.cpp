/* ANTv2
 * This file is part of ANTv2.
 * 
 * ANTv2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * ANTv2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with ANTv2.  If not, see <https://www.gnu.org/licenses/>.
 */


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

// open the About ANT dialog
void MainWindow::on_actionAboutReactiongame_triggered()
{
    // AboutGamewindow is everytime in foreground
    about_game.setModal(true);
    about_game.show();
}

// open the Instruction dialog
void MainWindow::on_actionInstructions_triggered()
{
    // show the instruction window everytime in the foreground
    instruction_dialog.setModal(true);
    instruction_dialog.show();
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
