#include "saving.h"
//SAVING
// protected functions for Saving class
// opens the csv file
bool Saving::OpenFile() {
    bool opened = file.open(QFile::WriteOnly);              // tries to open the csv file in write only mode
    return opened;                                          // true if the file is opened/created else false
}

// sets the qfile-descriptor
void Saving::SetQFileDescriptor(QString arg_ciphre, QString filetype){
        QString filename = CreateFilename(arg_ciphre, filetype);// creates the filename for the csv file
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
    ciphre_year_month_day_hour_minute(actuell time).arg_filetype
*/
QString Saving::CreateFilename(QString arg_ciphre, QString arg_filetype){
    // create the filename
    QDate date = QDate::currentDate();  // get the current date  (system clock)
    QTime time = QTime::currentTime();  // get the current time     -"-
    QString filename = arg_ciphre+"_"+date.toString("yyyy_MM_dd")+"_"+time.toString("hh_mm")+"."+arg_filetype;
    // returns the filename
    return filename;
}

//HTMLDOCUMENT
// public methods

// creates the HTML File
bool JSDocument::CreateJSFile(QString *arg_ciphre){
    bool ret;
    ciphre   = arg_ciphre;
    // names the file
    SetQFileDescriptor(*arg_ciphre,"js");
    //
    ret = OpenFile();
    if(!ret){
        cout << "[***] Error: Can't open File in CreateHTMLFile"<<endl;
        return false;
    }
    return true;
}

bool JSDocument::WriteJSFile(Calculation *c){
    QTextStream save(&file);        // output stream for a file
    // js file begin
    // user and test settings
    save << "var chiffre=\""<<*ciphre<<"\";";
    save << "var test_date=\""<<birthday<<"\";";
    // effects, error sum
    save << "var error_sum="<<c->GetErrorSum()<<";";
    save << "var conflict="<<c->GetConflict()<<";";
    save << "var orientation="<<c->GetOrientation()<<";";
    save << "var alertness="<<c->GetAlertness()<<";";
    // medians
    /*var median_rt   = "median reaction time";
    var non_cue_neutral     = "no cue neutral median";   // medians for no cue
    var non_cue_congruent   = "no cue congruent median";
    var non_cue_incongruent = "no cue incongruent median";
    var center_cue_neutral     = "center cue neutral median";   // medians for center cue
    var center_cue_congruent   = "center cue congruent median";
    var center_cue_incongruent = "center cue incongruent median";
    var double_cue_neutral     = "double cue neutral median";   // double for center cue
    var double_cue_congruent   = "double cue congruent median";
    var double_cue_incongruent = "double cue incongruent median";
    var spatial_cue_neutral     = "spatial cue neutral median";   // medians for spatial cue
    var spatial_cue_congruent   = "spatial cue congruent median";
    var spatial_cue_incongruent = "spatial cue incongruent median";*/
    // close file
    CloseFile();
    return true;
}

//CSVDOCUMENT
// public Methods
void CSVDocument::SetInformations(QString* arg_ciphre, QString* arg_birthday, QString* arg_comment){
    ciphre      = arg_ciphre;
    birthday    = arg_birthday;
    comment     = arg_comment;
}

// Creats the CSV file
bool CSVDocument::CreateCSVFile(){
    bool ret;
    // names the file
    SetQFileDescriptor(*ciphre, "csv");
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
    // set the Iterator to start
    arg_run->SetIteratorToStart();
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
        save << (i+1) <<",";
        // if the reaction time nder MINIMAL_REACTION_TIME => GetReactionTime isn't saved = missing value
        if(actuell_trial.GetReactionTime() > MINIMAL_REACTION_TIME)
            save <<actuell_trial.GetReactionTime() <<","<<actuell_trial.GetReaction();
        else
            save << "," << UNDER_MIN_REACTION;  // if the reaction time is under <= 100 ms the reaction of the trial = 0 = UNDER_MIN_REACTION
        // saves the positions of the stars and arrows
        save <<","<< cue <<","<<comb <<","<< pos << "," << mid <<","<<endl;
        if(!arg_run->NextTrial()){
            cout << "[***] Warning: Run->NextTrial return false in WriteCSVFile - CSVDocument" << endl;
            break;
        }
    }
    save << arg_run->GetPosition() <<","<<","<<",";
    save << *birthday <<","<<","<<","<<"," <<","<<*comment<<endl;
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
    if(!LookUpTablePos(arg_trial, arg_position))
        return false;

    // set the look up for midarrow
    if(!LookUpTableMid(arg_trial, arg_mid_arrow))
        return false;
    return true;
}

bool CSVDocument::LookUpTableCue(Trial *arg_trial, QString *arg_cue){
    // translate CUE = Star Position
    switch (arg_trial->GetCue()) {
    case TrialComponents::Cue::non_cue:
        *arg_cue = "no cue";
        break;
    case TrialComponents::Cue::center_cue:
        *arg_cue = "center cue";
        break;
    case TrialComponents::Cue::double_cue:
        *arg_cue = "double cue";
        break;
    case TrialComponents::Cue::spatial_cue_up:
        *arg_cue = "spatial cue up";
        break;
    case TrialComponents::Cue::spatial_cue_down:
        *arg_cue = "spatial cue down";
        break;
    default:
        *arg_cue = "cue error";
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
        *arg_position = "error position";
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
