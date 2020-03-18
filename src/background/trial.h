#ifndef TRIAL_H
#define TRIAL_H

#include <QtCore/QString>
#include <vector>

using namespace std;

class TrialComponents {
public:
    enum Cue {non_cue, center_cue, double_cue, spatial_cue_up, spatial_cue_down};   // where the star image is shown
    enum ArrowCombinations {neutral, congruent, incongruent};                       // how the arrows are combined i.e. ->-><-->->
    enum ArrowPositions {up, down};                 // Are the arrows over or under the plus sign
    enum DirectionMidArrow {left, right};           // in which direction points the mid arrow

    // all components a Trial is build from; first the Cue is shown than the arrows
    struct Components {
        Cue cue;
        ArrowCombinations combination;
        ArrowPositions position;
        DirectionMidArrow direction;
    };
};

class Trial : public TrialComponents
{
public:
    // Constructors
    Trial();    // for a Trial without a special Components combination
    // needed for run when special Components are create for the game
    Trial(Cue arg_cue, ArrowCombinations arg_arrow_combi, ArrowPositions arg_arrow_pos, DirectionMidArrow arg_arrow_dir);
    // Getter and Setter - reaction
    bool GetReaction() {return reaction;}
    void SetReaction(bool arg_reaction=false) {reaction = arg_reaction;}
    //      -"-          - reaction_time
    int GetReactionTime() {return reaction_time;}
    void SetReactionTime(int arg_reaction_time=-1) {reaction_time=arg_reaction_time;}
    //      -"-          - for Components (Setters aren't needed)
    // Cue:
    Cue GetCue() { return comp.cue;}
    // ArrowCombinations:
    ArrowCombinations GetArrowCombinations() {return comp.combination;}
    // ArrowPositions:
    ArrowPositions GetArrowPositions() {return comp.position;}
    // DirectionMidArrow
    DirectionMidArrow GetDirectionMidArrow() {return comp.direction;}

private:
    bool reaction;      // if the reaction is right or wrong
    int reaction_time;  // saves the reaction time - -1 is the standard setting
    Components comp;
};


#endif
