#include "run.h"

Run::Run(unsigned int runs){
    // Constructor fills the vector, clean the reaction variables and shuffels the vector
    AddRuns(runs);
    CleanMeasuredValues();
    run_length = v_trial.size();    // sets the run_length to the vector size
}


// public methods
// MEASUREMENT:
// controlls if the vector is at the end, (if not) saves the reactions and iterate the trial
bool Run::SetMeasuredValues(int arg_reaction_time, bool arg_reaction, bool arg_pressed){
    if(it_v_trial == v_trial.end())
    {
        cout << "[*] End of Trial vector reached!!!" << endl;
        return false;   // iterator reached the end of v_trial
    }
    if(GetPosition() == (run_length-1)){
        cout << "[*] End of Run Length - The next Trials aren't allowed" << endl;
        return false;
    }
    // sets the reactions
    it_v_trial->SetReactions(arg_reaction, arg_reaction_time, arg_pressed);

    return true;    // if the iterator isn't at the end - return true
}

// cleans, shuffels the vector and set the iterator to star
bool Run::CleanMeasuredValues(){
    // cleans all measured values
    for(it_v_trial = v_trial.begin();it_v_trial != v_trial.end();++it_v_trial){
        it_v_trial->SetReactions();
    }
    it_v_trial = v_trial.begin();   // iterator to start

    ShuffelTrialVector();   // shuffels the vector
    return true;
}

// TRIALS
// check if the next trial exist or goes to the start again
bool Run::NextTrial(){
    ++it_v_trial;                           // iterates the vector
    if(it_v_trial != v_trial.end()){        // check if the end of the vector was reached
        if(GetPosition() <= run_length)  // check if the Trial fits in run (run_length)
            return true;                    // not the end
    }
    // if the end was reached -> set iterator to the begin again and return false
    it_v_trial = v_trial.begin();
    return false;
}

// returns the actuel trial; it doesn't need a check the iterator is at the end,
// because NextTrial is the only way to iterate over
Trial Run::GetTrial(bool *size){
    // if the size is 0, we can't iterate over v_trial -> *size = false
    if(v_trial.size() == 0){
        Trial t;    // standard trial if the trial vector have the size 0
        cout << "[***] Error: Trial Vector have the size 0!!!" << endl;
        *size = false;
        return t;
    }
    // everything is ok!!!
    *size = true;
    return *it_v_trial;
}

// Setter RunLenght
void Run::SetRunLength(int arg_length){
    // if arg_length isn't in the interval 0 < x < v_trial.size()
    if(arg_length < v_trial.size() || arg_length > v_trial.size()){
        run_length = v_trial.size();
        return;
    }
    // arg_length fits in the vector size
    run_length = arg_length;
}


// private methods

// fill the trial vector
bool Run::FillTrialVector(){
    // for static cast
    TrialComponents::ArrowCombinations combination_cast;
    TrialComponents::ArrowPositions position_cast;
    TrialComponents::DirectionMidArrow direction_cast;
    // only usable if consecutive numerated - Trial only uses consecutive numerated enums
    // these three trial components are the same for every trial in the vector, but TrialComponents::Cue has spatial_cue,
    // which isn't add 2 times in the vector!!!
    for(int combinations = TrialComponents::ArrowCombinations::neutral; combinations <= TrialComponents::ArrowCombinations::incongruent; combinations++){
        for(int position = TrialComponents::ArrowPositions::up; position <= TrialComponents::ArrowPositions::down; position++){
            for(int direction = TrialComponents::DirectionMidArrow::left; direction <= TrialComponents::DirectionMidArrow::right; direction++){
                // cast the int of the iteration to the enums of TrialComponents
                combination_cast = static_cast<TrialComponents::ArrowCombinations>(combinations);
                position_cast = static_cast<TrialComponents::ArrowPositions>(position);
                direction_cast = static_cast<TrialComponents::DirectionMidArrow>(direction);
                // create a Trial with the given params and at it two or one time(s) at the trial vector
                CreateAndAddTrial(combination_cast, position_cast, direction_cast);
            }
        }
    }
    cout << "[**] FillVector: Size of Vector: " << v_trial.size() << endl;

    return true;
}

// Create a new Trial and add it to the trial vector
bool Run::CreateAndAddTrial(TrialComponents::ArrowCombinations arg_combi, TrialComponents::ArrowPositions arg_pos, TrialComponents::DirectionMidArrow arg_dir){
    // cast variable for cue
    TrialComponents::Cue cue_cast;

    // iterate over Cue every trial except the spatial Trial exist two times the spatial cue trial only one time
    for(int cue = TrialComponents::Cue::non_cue; cue <= TrialComponents::Cue::spatial_cue_down; cue++){
        cue_cast = static_cast<TrialComponents::Cue>(cue);
        v_trial.push_back(Trial(cue_cast, arg_combi, arg_pos, arg_dir));
        if(cue != TrialComponents::Cue::spatial_cue_up && cue != TrialComponents::spatial_cue_down)
            v_trial.push_back(Trial(cue_cast, arg_combi, arg_pos, arg_dir));
    }
    return true;
}

// adds a special number of Runs in the v_trial vector
bool Run::AddRuns(unsigned int arg_add){
    bool return_fill_vector = false;    // saves the return of FillTrialVector()
    // if no run was added return is false
    if(arg_add == 0)
        return false;
    // fills the vector
    for(unsigned int i = 0; i < arg_add; i++){
        return_fill_vector = FillTrialVector();
        if(!return_fill_vector) // something goes wrong in FillTrialVector
            return false;
    }
    return true;
}
