#include "saving.h"

// opens the csv file
bool Saving::openCSVFile() {
    bool opened = file.open(QFile::WriteOnly);              // tries to open the csv file in write only mode
    return opened;                                          // true if the file is opened/created else false
}

// sets the qfile-descriptor
void Saving::setQFileDescriptor(QString name, QString forename){
        QString filename = createFilename(name, forename);      // creates the filename for the csv file
        file.setFileName(filename);                             // sets the filename of the file
}

// write in the csv file
void Saving::writeCSVFile(Run *run, QString comment, QString birthday) {
    /*
        Input of a csv-file:
        trial number, reaction time*, reacted**, average***, right percentage***, median***, effects***, comment***
        *   is the measured rection time or if no reaction the waiting time
        **  true if there was a reaction false if not
        *** all values from Calculation
    */
    Calculation calc;
    int number_of_rows = 1;         // count the number of colums
    QTextStream save(&file);        // output stream for a file
    // saves the headline in the csv file
    // save << "trial number,reaction time,right desicion,median,average,percentage of right decisions,effects,comment,birthday"<< endl;
    save << "trial number,reaction time,right desicion,median,average,percentage of right decisions,birthday,comment"<< endl;
    // runs solong elements in the vector
    run->setIteratorToStart();      // start the iterator at the beginn
    while (run->readRun()) {
        save << number_of_rows<<"," << run->getActuellTrial().getReactionTime() << ",";
         // save if the reaction was right
        if (run->getActuellTrial().getRightReaction())
            save << "true"<< endl;
        else
            save << "false"<< endl;
        ++number_of_rows;
    }
    // calc the values
    calc.calcValues(run);
    // saves all calculated and measured values
    // save << ",,,"<<calc.getMedian()<<","<<calc.getAverage()<<","<<calc.getRightPercentage()<<","<<calc.getEffects()<<","<<comment<<","<<birthday<<endl;
    save << ",,,"<<calc.getMedian()<<","<<calc.getAverage()<<","<<calc.getRightPercentage()<<","<<","<<birthday<<","<<comment<<endl;
    calc.resetValues(); // reset all calculated values
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
    QDate date = QDate::currentDate();  // get the current date  (system clock)
    QTime time = QTime::currentTime();  // get the current time     -"-
    QString filename = name+"_"+forename+"_"+date.toString("yyyy_MM_dd")+"_"+time.toString("hh_mm")+".csv";
    // returns the filename
    return filename;
}
