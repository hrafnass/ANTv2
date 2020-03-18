#ifndef TRIAL_H
#define TRIAL_H

#include <QtCore/QString>
#include <vector>

class TrialComponents {
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

class Trial
{
public:

private:

};


#endif
