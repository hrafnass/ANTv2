#include "trial.h"

// Constructor for a neutral Trial
Trial::Trial(){
    SetTrial();
}

Trial::Trial(Cue arg_cue, ArrowCombinations arg_arrow_combi, ArrowPositions arg_arrow_pos, DirectionMidArrow arg_arrow_dir){
    SetTrial(arg_cue, arg_arrow_combi, arg_arrow_pos, arg_arrow_dir);
}





// public Methods:



// private Methods:

void Trial::SetTrial(Cue arg_cue, ArrowCombinations arg_arrow_combi, ArrowPositions arg_arrow_pos, DirectionMidArrow arg_arrow_dir){
    SetComponents(arg_cue, arg_arrow_combi, arg_arrow_pos, arg_arrow_dir);
    SetReactions();
}
