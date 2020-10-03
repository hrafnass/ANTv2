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
