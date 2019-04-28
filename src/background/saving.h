#ifndef SAVING_H
#define SAVING_H
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QTime>
#include <QDate>

#include "calculation.h"
#include "run.h"

// Saves all calculated and measured data of the reaction game in  a csv file
class Saving
{
public:
    Saving();
    bool openCSVFile(QString name, QString forename);                                   // open a new csv-file
    void writeCSVFile(Run *run, Calculation *calc, QString comment);           // saves all calculated and measured values
    void closeCSVFile();                                                                // closes the csv-file
private:
    // functions
    QString createFilename(QString name, QString forename);         // creates a new filename for the csv-file
    // variables
    QFile file;                 // saves the "qt-file descriptor"
    QDate date;                 // saves the qdate object for the filename
    QTime time;                 // saves the qtime object for the filename
};

#endif // SAVING_H
