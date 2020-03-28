#include "saving.h"
//SAVING
// protected functions for Saving class
// opens the csv file
bool Saving::OpenFile() {
    bool opened = file.open(QFile::WriteOnly);              // tries to open the csv file in write only mode
    return opened;                                          // true if the file is opened/created else false
}

// sets the qfile-descriptor
void Saving::SetQFileDescriptor(QString name, QString forename, QString filetype){
        QString filename = CreateFilename(name, forename, filetype);// creates the filename for the csv file
        file.setFileName(filename);                             // sets the filename of the file
        cout << "filename"<<endl;
}

// closes the csv file
void Saving::CloseFile(){
    file.close();
    return;
}

/*
    The name of a csv/html file is build in that way:
    forename_name_year_month_day_hour_minute.
    CreateFilename create everything before the dot+filetype
*/
QString Saving::CreateFilename(QString name, QString forename, QString filetype){
    // create the filename
    QDate date = QDate::currentDate();  // get the current date  (system clock)
    QTime time = QTime::currentTime();  // get the current time     -"-
    QString filename = name+"_"+forename+"_"+date.toString("yyyy_MM_dd")+"_"+time.toString("hh_mm")+"."+filetype;
    // returns the filename
    return filename;
}

//HTMLDOCUMENT
// public methods

// creates the HTML File
bool HTMLDocument::CreateHTMLFile(QString *name, QString *fname){
    bool ret;
    // names the file
    SetQFileDescriptor(*name,*fname,"html");
    //
    ret = OpenFile();
    if(!ret){
        cout << "[***] Error: Can't open File in CreateHTMLFile"<<endl;
        return false;
    }
    return true;
}

bool HTMLDocument::WriteHTMLFile(Calculation *c){
    QTextStream save(&file);        // output stream for a file

    save << "<html><body>Not written yet!!!</body></html>"<<endl;
    return true;
}

//CSVDOCUMENT
// public Methods
void CSVDocument::SetInformations(QString* arg_name, QString* arg_forename, QString* arg_birthday, QString* arg_comment){
    name = arg_name;
    forename = arg_forename;
    birthday = arg_birthday;
    comment = arg_comment;
}

// Creats the CSV file
bool CSVDocument::CreateCSVFile(){
    bool ret;
    // names the file
    SetQFileDescriptor(*name,*forename,"csv");
    ret = OpenFile();
    if(!ret){
        cout << "[***] Error: Can't open File in CreateCSVFile"<<endl;
        return false;
    }
    return true;
}

bool CSVDocument::WriteCSVFile(Run *arg_run){
    QString cue, comb, pos, mid;    // Strings for the lookup table
    bool in_size = false;
    Trial actuell_trial;
    QTextStream save(&file);        // output stream for a file
    // csv table head
    save << "trial number,reaction time,right desicion,birthday,cue,combinations,position,position mid arrow,comment"<< endl;
    // csv table body
    for(unsigned int i=0; i < arg_run->GetRunLength(); ++i){
        // paint stars
        actuell_trial = arg_run->GetTrial(&in_size);
        if(!LookUpTable_Trial(&actuell_trial, &cue, &comb, &pos, &mid)){
                cout << "Quit WriteCSVFile" << endl;
                CloseFile();
                return false;
        }
        // save i-th number line of the body
        save << i <<","<<actuell_trial.GetReactionTime() <<","<<actuell_trial.GetReaction() <<","<<birthday <<","<< actuell_trial.GetCue();
        save <<","<<actuell_trial.GetArrowCombinations() <<","<< actuell_trial.GetArrowPositions() << "," << actuell_trial.GetDirectionMidArrow()<<","<<comment<<endl;
        if(!arg_run->NextTrial()){
            cout << "[***] Warning: Run->NextTrial return false in WriteCSVFile - CSVDocument" << endl;
            break;
        }
    }
    CloseFile();
    return true;
}

// private Methods
bool CSVDocument::LookUpTable_Trial(Trial *arg_trial, QString *arg_cue, QString *arg_combinations, QString *arg_position, QString *arg_mid_arrow){
    if(arg_trial == nullptr)
        return false;

    // set the look up for Cue
    if(!LookUpTableCue(arg_trial, arg_cue))
        return false;

    // set the look up for combinations
    if(!LookUpTableComb(arg_trial, arg_combinations))
        return false;

    // set the look up for position
    if(!LookUpTableComb(arg_trial, arg_position))
        return false;

    // set the look up for midarrow
    if(!LookUpTableComb(arg_trial, arg_mid_arrow))
        return false;

    return true;
}

bool CSVDocument::LookUpTableCue(Trial *arg_trial, QString *arg_cue){
    // translate CUE = Star Position
    switch (arg_trial->GetCue()) {
    case TrialComponents::Cue::non_cue:
        *arg_cue = "non_cue";
        break;
    case TrialComponents::Cue::center_cue:
        *arg_cue = "center_cue";
        break;
    case TrialComponents::Cue::double_cue:
        *arg_cue = "double_cue";
        break;
    case TrialComponents::Cue::spatial_cue_up:
        *arg_cue = "spatial_cue_up";
        break;
    case TrialComponents::Cue::spatial_cue_down:
        *arg_cue = "spatial_cue_down";
        break;
    default:
        *arg_cue = "cue_error";
        cout << "[***] Error: Can't fine Cue"<< endl;
        return false;
    }

    return true;
}

bool CSVDocument::LookUpTableComb(Trial *arg_trial, QString *arg_combinations){
    // Translate arrowcombinations
    switch (arg_trial->GetArrowCombinations()) {
    case TrialComponents::ArrowCombinations::neutral:
        *arg_combinations = "neutral";
        break;
    case TrialComponents::ArrowCombinations::congruent:
        *arg_combinations = "congruent";
        break;
    case TrialComponents::ArrowCombinations::incongruent:
        *arg_combinations = "incongruent";
        break;
    default:
        cout << "[***] Error: Error in LookUpTableComb"<<endl;
        *arg_combinations = "error_combinations";
        return false;
    }

    return true;
}

bool CSVDocument::LookUpTablePos(Trial *arg_trial, QString *arg_position){
    switch (arg_trial->GetArrowPositions()) {
    case TrialComponents::ArrowPositions::up:
        *arg_position = "up";
        break;
    case TrialComponents::ArrowPositions::down:
        *arg_position = "down";
        break;
    default:
        *arg_position = "error_position";
        cout << "[***] Error: Error in LookUpTablePos" << endl;
        return false;
    }
    return true;
}

bool CSVDocument::LookUpTableMid(Trial *arg_trial, QString *arg_mid_arrow){
    switch (arg_trial->GetDirectionMidArrow()) {
    case TrialComponents::DirectionMidArrow::left:
        *arg_mid_arrow = "left";
        break;
    case TrialComponents::DirectionMidArrow::right:
        *arg_mid_arrow = "right";
        break;
    default:
        *arg_mid_arrow = "error_mid_arrow";
        cout << "[***]Errror: Error in LookUpTableMid" << endl;
        return false;
    }

    return true;
}
