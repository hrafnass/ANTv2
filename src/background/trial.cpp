#include "trial.h"

// TRIALCCOMPONENTS CLASS
// protected Methods
void TrialComponents::SetInnerArrow(DirectionMidArrow arg_dir_mid_arrow){
    // saves the fitting svg image path in arrow_inner
    switch (arg_dir_mid_arrow) {
    case left   : arrow_inner = ARROW_LEFT; break;
    case right  : arrow_inner = ARROW_RIGHT; break;
    default: cout << "[***] Error: Can't find an image, that fits." << endl;
    }
}


// TRIAL CLASS
// Constructor for a neutral Trial
Trial::Trial(){
    SetTrial();
}

Trial::Trial(Cue arg_cue, ArrowCombinations arg_arrow_combi, ArrowPositions arg_arrow_pos, DirectionMidArrow arg_arrow_dir){
    SetTrial(arg_cue, arg_arrow_combi, arg_arrow_pos, arg_arrow_dir);
}

// public Methods:
// sets reaction time and the reaction
void Trial::SetReactions(bool arg_reaction, int arg_reaction_time){
    reaction = arg_reaction;
    reaction_time = arg_reaction_time;
    cout << "[*] SetReaction: " << reaction << " " << reaction_time << endl;
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
    SetComponents(arg_cue, arg_arrow_combi, arg_arrow_pos, arg_arrow_dir);
    SetReactions();
}
