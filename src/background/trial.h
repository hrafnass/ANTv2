#ifndef TRIAL_H
#define TRIAL_H

#include <QtCore/QString>
#include <vector>
#include <iostream>

#define ARROW_LEFT ":/ressources/images/arrow_left.svg"
#define ARROW_RIGHT ":/ressources/images/arrow_right.svg"
#define BAR ":/ressources/images/bar.svg"
#define STAR ":/ressources/images/star.svg"

using namespace std;

class TrialComponents {
public:
    TrialComponents();
    // Getter for arrow and star image
    QString GetInnerArrow(){ return arrow_inner;}
    QString GetOuterArrow(){ return arrow_outer;}
protected:
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

    void SetInnerArrow(DirectionMidArrow arg_dir_mid_arrow);
    void SetOuterArrow(ArrowCombinations arg_arrow_combination);

private:
    // saves the image paths
    QString arrow_inner = "";
    QString arrow_outer = "";   // outer arrows also can be bar.svg
    QString star = STAR;
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
    //      -"-          - reaction_time
    int GetReactionTime() {return reaction_time;}
    // Setter for reaction and reaction_time - only exist together
    void SetReactions(bool arg_reaction = false, int arg_reaction_time = -1);
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
    // sets the Component for the Constructor
    void SetComponents(Cue arg_cue=non_cue, ArrowCombinations arg_arrow_combi=neutral, ArrowPositions arg_arrow_pos=down, DirectionMidArrow arg_arrow_dir=left);
    // all variables for the Constructor
    void SetTrial(Cue arg_cue=non_cue, ArrowCombinations arg_arrow_combi=neutral, ArrowPositions arg_arrow_pos=down, DirectionMidArrow arg_arrow_dir=left);    // setter for the Trial-Constructor

    bool reaction;      // if the reaction is right or wrong
    int reaction_time;  // saves the reaction time - -1 is the standard setting
    Components comp;

};


#endif
