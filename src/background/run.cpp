#include "run.h"

Run::Run(){
    // Constructor fills the vector, clean the reaction variables and shuffels the vector
    FillTrialVector();
    CleanMeasuredValues();
}


// public methods
// cleans and shuffels the vector
bool Run::CleanMeasuredValues(){
    // cleans all measured values

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
