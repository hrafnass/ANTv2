#include "run.h"

Run::Run(int runs){
    // Constructor fills the vector, clean the reaction variables and shuffels the vector
    AddRuns(runs);
    CleanMeasuredValues();
}


// public methods
// controlls if the vector is at the end, (if not) saves the reactions and iterate the trial
bool Run::SetMeasuredValues(int arg_reaction_time, bool arg_reaction){
    if(it_v_trial != v_trial.end())
    {
        cout << "[*] End of Trial vector reached!!!" << endl;
        return false;   // iterator reached the end of v_trial
    }
    // sets the reactions
    it_v_trial->SetReactions(arg_reaction, arg_reaction_time);
    // iterates the the iterator
    ++it_v_trial;

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
    bool return_fill_vector = false;

    if(arg_add == 0)
        return false;

    for(int i = 0; i < arg_add; i++){
        return_fill_vector = FillTrialVector();
        if(!return_fill_vector)
            return false;
    }
    return true;
}
