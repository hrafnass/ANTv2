#include "trial.h"

// TRIALCCOMPONENTS CLASS
// protected Methods
void TrialComponents::SetInnerArrow(DirectionMidArrow arg_dir_mid_arrow){
    // saves the fitting svg image path in arrow_inner
    switch (arg_dir_mid_arrow) {
    case left   : arrow_inner = ARROW_LEFT; break;  // inner arrow points to the left
    case right  : arrow_inner = ARROW_RIGHT; break; //              -"-          right
    default: cout << "[***] Error(SetInnerArrow): Can't find an image, that fits." << endl;
    }
}

void TrialComponents::SetOuterArrow(ArrowCombinations arg_arrow_combination){
    switch (arg_arrow_combination) {
    case neutral    : arrow_outer = BAR; break;         // the outer images are bar.svg
    case congruent  : arrow_outer = arrow_inner; break; // inner and outer arrow are the same
    case incongruent:
        if(arrow_inner == ARROW_LEFT)   // ->-><-->->
            arrow_outer = ARROW_RIGHT;
        else
            arrow_outer = ARROW_LEFT;   // <-<--><-<-
        break;
    default: cout << "[***] Error(SetOuterArrow): Can't find an image, that fits." << endl;
    }
}

// TRIAL CLASS
// Constructor for a neutral Trial
Trial::Trial(){
    SetTrial();
}

Trial::Trial(TrialComponents::Cue arg_cue, TrialComponents::ArrowCombinations arg_arrow_combi, TrialComponents::ArrowPositions arg_arrow_pos, TrialComponents::DirectionMidArrow arg_arrow_dir){
    SetTrial(arg_cue, arg_arrow_combi, arg_arrow_pos, arg_arrow_dir);
}

// public Methods:
// sets reaction time and the reaction
void Trial::SetReactions(bool arg_reaction, int arg_reaction_time, bool arg_pressed){
    reaction = arg_reaction;
    reaction_time = arg_reaction_time;
    was_pressed = arg_pressed;
    //cout << "[*] SetReaction: " << reaction << " " << reaction_time << " " << was_pressed << endl;
}


// private Methods:

// Setter for Components
void Trial::SetComponents(Cue arg_cue, ArrowCombinations arg_arrow_combi, ArrowPositions arg_arrow_pos, DirectionMidArrow arg_arrow_dir){
    comp.cue = arg_cue;
    comp.combination = arg_arrow_combi;
    comp.position = arg_arrow_pos;
    comp.direction = arg_arrow_dir;
}

// Setter for Trial(...)
void Trial::SetTrial(Cue arg_cue, ArrowCombinations arg_arrow_combi, ArrowPositions arg_arrow_pos, DirectionMidArrow arg_arrow_dir){
    // fills comp
    SetComponents(arg_cue, arg_arrow_combi, arg_arrow_pos, arg_arrow_dir);
    // sets the image paths
    SetInnerArrow(comp.direction);
    SetOuterArrow(comp.combination);
    // sets reaction and reaction time
    SetReactions();
}
