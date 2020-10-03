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


#ifndef SAVEDIALOG_H
#define SAVEDIALOG_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QAbstractButton>

// background functions
#include "src/background/run.h"
// classes for values and saving
#include "src/background/saving.h"
#include "src/background/calculation.h"

namespace Ui {
class SaveDialog;
}

class SaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveDialog(QWidget *parent = nullptr);
    ~SaveDialog();
    // Setter for all needed values
private slots:
    void acceptSaveDialog(){ this->done(QDialog::Accepted);}
private:
    // Variables
    Ui::SaveDialog *ui;
};

#endif // SAVEDIALOG_H
