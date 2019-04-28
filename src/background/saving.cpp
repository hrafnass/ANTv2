#include "saving.h"

Saving::Saving(){
    time = QTime::currentTime();    // init the qtime object
    date = QDate::currentDate();    // init the qdate object
}

// opens the csv file
bool Saving::openCSVFile(QString name, QString forename) {
    QString filename = createFilename(name, forename);      // creates the filename for the csv file
    file.setFileName(filename);                     // sets the filename of the file
    bool opened = file.open(QIODevice::WriteOnly);  // tries to open the csv file in write only mode
    return opened;                                  // true if the file is opened/created else false
}

// write in the csv file
void Saving::writeCSVFile(vector<Trial> run, Calculation *calc, QString comment) {
    /*
        Input of a csv-file:
        trial number, reaction time*, reacted**, average***, right percentage***, median***, effects***, comment***
        *   is the measured rection time or if no reaction the waiting time
        **  true if there was a reaction false if not
        *** all values from Calculation
    */
    QTextStream save(&file);       // output stream for a file
    // saves the headline in the csv file
    save << "trial number,reaction time,right desicion,median,average,percentage of right decisions,effects,comment,finished test" << endl;
    // saves all calculated and measured values
    save << "0,reaction time,right reaction,star position,arrow position,kind of img"<<QString::number(calc->getMedian())<<","<<QString::number(calc->getAverage())<<","<<QString::number(calc->getRightPercentage())<<","<<QString::number(calc->getEffects())<<","<<comment<<endl;

    return;
}

// closes the csv file
void Saving::closeCSVFile(){
    file.close();
    return;
}

// creates the csv filename
/*
    The name of a csv file is build in that way:
    forename_name_year_month_day_hour_minute.csv
*/
QString Saving::createFilename(QString name, QString forename){
    // create the filename
    QString filename = name+"_"+forename+"_"+date.toString("yyyy_MM_dd")+"_"+time.toString("hh_mm")+".csv";
    // returns the filename
    return filename;
}
