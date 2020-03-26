#include "saving.h"

// opens the csv file
bool Saving::OpenCSVFile() {
    bool opened = file.open(QFile::WriteOnly);              // tries to open the csv file in write only mode
    return opened;                                          // true if the file is opened/created else false
}

// sets the qfile-descriptor
void Saving::SetQFileDescriptor(QString name, QString forename){
        QString filename = CreateFilename(name, forename);      // creates the filename for the csv file
        file.setFileName(filename);                             // sets the filename of the file
}

// closes the csv file
void Saving::CloseCSVFile(){
    file.close();
    return;
}

// creates the csv filename
/*
    The name of a csv file is build in that way:
    forename_name_year_month_day_hour_minute.csv
*/
QString Saving::CreateFilename(QString name, QString forename){
    // create the filename
    QDate date = QDate::currentDate();  // get the current date  (system clock)
    QTime time = QTime::currentTime();  // get the current time     -"-
    QString filename = name+"_"+forename+"_"+date.toString("yyyy_MM_dd")+"_"+time.toString("hh_mm")+".csv";
    // returns the filename
    return filename;
}
