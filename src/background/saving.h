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
public:
    bool openCSVFile(QString name, QString forename);                                   // open a new csv-file
    void writeCSVFile(Run *run, Calculation *calc, QString comment, QString birthday);           // saves all calculated and measured values
    void closeCSVFile();                                                                // closes the csv-file
private:
    // functions
    QString createFilename(QString name, QString forename);         // creates a new filename for the csv-file
    // variables
    QFile file;                 // saves the "qt-file descriptor"
};

#endif // SAVING_H
