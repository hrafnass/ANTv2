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


#ifndef SAVING_H
#define SAVING_H

#define MINIMAL_REACTION_TIME 150    // the minimal reaction time is 100 ms
#define UNDER_MIN_REACTION 0         // our reaction time is a missing value => Reation of trial = 0

#include <QtCore/QDate>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtCore/QTextStream>
#include <QtCore/QTime>

#include "calculation.h"
#include "run.h"


/* ***********************************************************************************************
 * Directory Structure:                                                                          *
 *  measurements/        (root dir for all measurements)                                         *
 *              /ciphre_year_month_day_hour_min  (every ciphre - test person get his own folder) *            *
 * --------------------------------------------------------------------------------------------- *
 * Files in ciphre:                                                                              *
 *      ciphre.csv   (all measured values in this run)                                           *
 *      print.html              (out if the run was finished successful)                         *
 *      val.js    ( -"-)                                                                         *     *
 * ***********************************************************************************************/

// Saves all calculated and measured data of the reaction game in  a csv file
class Saving
{
public:
    // getter and setter for time and date
    QTime GetTime() { return time;}
    QDate GetDate() { return date;}
    void SetTimeAndDate();
protected:
    // open and close a file descriptor
    bool OpenFile();     // open a new file
    void CloseFile();    // closes the file
    // qfile descriptor settings
    // set the standard settings for the qfile-descriptor and create a file directory
    void SetQFileDescriptor(QString arg_ciphre, QString arg_filename, QString filetype);
    // functions
    // creates a new filename for the csv-file
    QString CreateFilename(QString arg_filename, QString filetype, bool dir);
    // variables
    QFile file;                 // saves the "qt-file descriptor"
    // Date and time
    QDate date;
    QTime time;
private:
    bool CreateDirs(QString arg_ciphre);    // creates the dir structure
};

class JSDocument : public Saving {
public:
    bool CreateJSFile(QString *arg_ciphre, QDate* arg_date, QTime* arg_time); // Creates the JS-File
    bool WriteJSFile(Run* arg_run); // Writes the JS-File and Close it
private:
    QString *ciphre;
    QString *birthday;

    Calculation c;
};


class CSVDocument : public Saving {
public:
    bool CreateCSVFile();   // Creates the CSV saving file
    // write and close the file
    bool WriteCSVFile(Run *arg_run);
    // setter for all informations
    void SetInformations(QString* arg_ciphre, QString* arg_birthday, QString* arg_comment);// saves all calculated and measured values
private:
    // transforms the enum values into strings i.e. non_cue for 0 into "non_cue"
    bool LookUpTable_Trial(Trial *arg_trial, QString* arg_cue, QString* arg_combinations, QString* arg_position, QString* arg_mid_arrow);
    bool LookUpTableCue(Trial *arg_trial, QString* arg_cue);
    bool LookUpTableComb(Trial *arg_trial, QString* arg_combinations);
    bool LookUpTablePos(Trial *arg_trial, QString* arg_position);
    bool LookUpTableMid(Trial *arg_trial, QString* arg_mid_arrow);

    QString* ciphre;
    QString* birthday;
    QString* comment;
};

#endif // SAVING_H
