#ifndef SAVING_H
#define SAVING_H
/*
#include <QtCore/QDate>
#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtCore/QTextStream>
#include <QtCore/QTime>

//#include "calculation.h"
#include "run.h"

// Saves all calculated and measured data of the reaction game in  a csv file
class Saving
{
public:
    // open and close a file descriptor
    bool openCSVFile();                                                                 // open a new csv-file
    void closeCSVFile();                                                                // closes the csv-file
    // qfile descriptor settings
    void setQFileDescriptor(QString name, QString forename);                            // set the standard settings for the qfile-descriptor
private:
    // functions
    QString createFilename(QString name, QString forename);         // creates a new filename for the csv-file
    // variables
    QFile file;                 // saves the "qt-file descriptor"
};

class HTMLDocument : public Saving {
public:
    writeHTMLFile(Calculation *arg_calc);
};


class CSVDocument : public Saving {
public:
    // write
    void writeCSVFile(Run *run, QString comment, QString birthday);                     // saves all calculated and measured values
};
*/
#endif // SAVING_H
