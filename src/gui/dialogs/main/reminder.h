/* ANTv2
 * Copyright (C) 2020 Siegfried Gauggel
 * Copyright (C) 2020 Marcel Gräfenstein
 * 
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


#ifndef REMINDER_H
#define REMINDER_H

#include <QtWidgets/QDialog>
namespace Ui {
class Reminder;
}

class Reminder : public QDialog
{
    Q_OBJECT

public:
    explicit Reminder(QWidget *parent = nullptr);
    ~Reminder();

private:
    Ui::Reminder *ui;
};

#endif // REMINDER_H
