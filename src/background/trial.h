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

/* ******************************************************************
 * A Trial is the combination of stars (cue) and five arrows.       *
 * First the/no star(s) is shown and then the arrows.               *
 * Example:                                                         *
 *                                                                  *
 *      *                   <-<-<-<-<-                              *
 *      +   ----------->         +                                  *
 *      *                    - - - - -                              *
 *                                                                  *
 * The player should react how fast he could and find out in which  *
 * direction (DirectionMidArrow) the mid arrow points. The Trial-   *
 * Components have all needed informations to show a Trial in the   *
 * GameWindow-Class. The image path of the inner and outer arrow(s) *
 * and the arrow and cue combination for a Trial.                   *
 * -----------------------------------------------------------------*
 * The Trial-Class has two Constructors (a standard Trial and a     *
 * specialized). The Trial Class saves the TrialComponents and the  *
 * reaction time and reaction (measured in the game).               *
 * ******************************************************************/

class TrialComponents {
public:
    //TrialComponents();
    // Getter for arrow and star image
    QString GetInnerArrow(){ return arrow_inner;}
    QString GetOuterArrow(){ return arrow_outer;}

    enum Cue {non_cue, center_cue, double_cue, spatial_cue_up, spatial_cue_down};   // where the star image is shown
    enum ArrowCombinations {neutral, congruent, incongruent};                       // how the arrows are combined i.e. ->-><-->->
    enum ArrowPositions {up, down};                 // Are the arrows over or under the plus sign
    enum DirectionMidArrow {left, right};           // in which direction points the mid arrow
protected:
    void SetInnerArrow(DirectionMidArrow arg_dir_mid_arrow);
    void SetOuterArrow(ArrowCombinations arg_arrow_combination);

    // all components a Trial is build from; first the Cue is shown than the arrows
    struct Components {
        Cue cue;
        ArrowCombinations combination;
        ArrowPositions position;
        DirectionMidArrow direction;
    };
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
    Trial(TrialComponents::Cue arg_cue, TrialComponents::ArrowCombinations arg_arrow_combi, TrialComponents::ArrowPositions arg_arrow_pos, TrialComponents::DirectionMidArrow arg_arrow_dir);
    // Getter and Setter - reaction
    bool GetReaction() {return reaction;}
    //      -"-          - reaction_time
    int GetReactionTime() {return reaction_time;}
    bool GetPressed() {return was_pressed;}
    // Setter for reaction and reaction_time - only exist together
    void SetReactions(bool arg_reaction = false, int arg_reaction_time = -1, bool arg_pressed = false);
    //      -"-          - for Components (Setters aren't needed)
    // Cue:
    TrialComponents::Cue GetCue() { return comp.cue;}
    // ArrowCombinations:
    TrialComponents::ArrowCombinations GetArrowCombinations() {return comp.combination;}
    // ArrowPositions:
    TrialComponents::ArrowPositions GetArrowPositions() {return comp.position;}
    // DirectionMidArrow
    TrialComponents::DirectionMidArrow GetDirectionMidArrow() {return comp.direction;}

private:
    // sets the Component for the Constructor
    void SetComponents(TrialComponents::Cue arg_cue=non_cue, TrialComponents::ArrowCombinations arg_arrow_combi=neutral, TrialComponents::ArrowPositions arg_arrow_pos=down, TrialComponents::DirectionMidArrow arg_arrow_dir=left);
    // all variables for the Constructor
    void SetTrial(TrialComponents::Cue arg_cue=non_cue, TrialComponents::ArrowCombinations arg_arrow_combi=neutral, TrialComponents::ArrowPositions arg_arrow_pos=down, TrialComponents::DirectionMidArrow arg_arrow_dir=left);    // setter for the Trial-Constructor

    bool reaction;      // if the reaction is right or wrong
    int reaction_time;  // saves the reaction time - -1 is the standard setting
    bool was_pressed;   // saves if a key(right or wrong) was pressed
    TrialComponents::Components comp;

};


#endif
