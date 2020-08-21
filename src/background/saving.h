#ifndef SAVING_H
#define SAVING_H

#include <QtCore/QDate>
#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtCore/QTextStream>
#include <QtCore/QTime>

#include "calculation.h"
#include "run.h"

// Saves all calculated and measured data of the reaction game in  a csv file
class Saving
{
protected:
    // open and close a file descriptor
    bool OpenFile();                                                                 // open a new csv-file
    void CloseFile();                                                                // closes the csv-file
    // qfile descriptor settings
    void SetQFileDescriptor(QString arg_ciphre, QString filetype);          // set the standard settings for the qfile-descriptor
    // functions
    QString CreateFilename(QString arg_ciphre, QString filetype);         // creates a new filename for the csv-file
    // variables
    QFile file;                 // saves the "qt-file descriptor"
};

class HTMLDocument : public Saving {
public:
    bool CreateHTMLFile(QString *arg_ciphre); // Creates the HTML File
    bool WriteHTMLFile(Calculation *c);                 // Writes the HTML FILE and Close it
private:
    QString *ciphre;
    QString *birthday;
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

    QString* name;
    QString* forename;
    QString* birthday;
    QString* comment;
};

#endif // SAVING_H
