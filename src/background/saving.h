#ifndef SAVING_H
#define SAVING_H

#define MINIMAL_REACTION_TIME 100    // the minimal reaction time is 100 ms
#define UNDER_MIN_REACTION 0         // our reaction time is a missing value => Reation of trial = 0

#include <QtCore/QDate>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtCore/QTextStream>
#include <QtCore/QTime>

#include "calculation.h"
#include "run.h"


/* ***********************************************************************************
 * Directory Structure:                                                              *
 *  measurements/        (root dir for all measurements)                             *
 *              /ciphre  (every ciphre - test person get his own folder)             *
 * --------------------------------------------------------------------------------- *
 * Files in ciphre:                                                                  *
 *      ciphre_year_month_day_hour_minute.csv   (all measured values in this run)    *
 *      print.html              (out if the run was finished successful)             *
 *      year_month_minute.js    ( -"-)                                               *
 * --------------------------------------------------------------------------------- *
 * print.html has an input script to find out the right js document.                 *
 * ***********************************************************************************/

// Saves all calculated and measured data of the reaction game in  a csv file
class Saving
{
protected:
    // open and close a file descriptor
    bool OpenFile();     // open a new file
    void CloseFile();    // closes the file
    // qfile descriptor settings
    // set the standard settings for the qfile-descriptor and create a file directory
    void SetQFileDescriptor(QString arg_ciphre, QString filetype);
    // functions
    QString CreateFilename(QString arg_ciphre, QString filetype);  // creates a new filename for the csv-file
    // variables
    QFile file;                 // saves the "qt-file descriptor"
private:
    bool CreateDirs(QString arg_ciphre);    // creates the dir structure
};

class JSDocument : public Saving {
public:
    bool CreateJSFile(QString *arg_ciphre); // Creates the JS-File
    bool WriteJSFile(Run* arg_run);         // Writes the JS-File and Close it
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
