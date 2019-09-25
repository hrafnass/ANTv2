#ifndef TRIAL_H
#define TRIAL_H

#include <QtCore/QString>
#include <vector>

using namespace std;

/*  A Trial is a combination of 5 arrows (allowed combis saved in image), the positions of the arrows
 *  (arrow_position) and the position of the stars (star_positions), which are shown between the arrow combis.
 *  With this trials we want to check, how fast a person could check in which direction (dir) the mid arrow points.
 *  Needed characteristics: - check if it was measured      (measured)
 *                          - direction of the mid arrow    (direction)
 *                          - reaction time for a check     (reaction_time)
 *                          - was the reaction right        (right_reaction)
 *                          - the names for the arrow imgs  (mid_img, other_img)
 *                          - positions of star(s),arrows,...   (star_pos, arrow_pos, img)
 *
 *  A Trial is used in the Run-Class. There are all needed/wanted trials saved in a run_vector and show by the gui
 *  in the gameloop.
 *
 *  FOR THE STANDARDIZED TEST YOU RUN ALL COMBINATIONS OF IMAGE, STAR_POSITION, ARROW_POSITION THREE TIMES WITH A PAUSE
 *  BETWEEN EVERY X % 72 = 0 COMBI.
 **/

// Trial is the show of one arrow with one star
class Trial
{
public:
    // all needed enums
    // images
    typedef enum {
        lllll,
        rrlrr,
        sslss,
        rrrrr,
        llrll,
        ssrss
    } image;
    // starposition
    typedef enum {
        up_star,
        down_star,
        mid,
        both_star
    } star_position;
    // arrowposition
    typedef enum{
        up_arrow,
        down_arrow,
        both_arrow
    }  arrow_position;
    // saves the direction of the mid arrow
    typedef enum  {
        l,      // left
        r       // right
    } dir;
    Trial(){}
    Trial(star_position star_pos, arrow_position arrow_pos, image img);
    // setter for trial
    void setReactionTime(int time);                     // set the reaction time
    void setRightReaction(bool reaction);               // set the reaction
    // getter for trial
    // measured values
    int getReactionTime();
    bool getRightReaction();
    // picture positions
    star_position getStarPosition();
    arrow_position getArrowPosition();
    dir getDirection();
    // return other and mid_img
    QString getMidImg();
    QString getOtherImg();
    // getter and setter for measure
    void setMeasure(bool m) { measured = m;}
    bool getMeasure() { return measured;}
private:
    // private methods
    void setDirection();        // the direction value
    void setImg();
    // saves the positions of the star and the arrows and which images should be shown
    star_position star_pos;
    arrow_position arrow_pos;
    image img;
    // saves the direction of the arrow
    dir direction;
    // saves the values of the reaction
    bool right_reaction;        // is the reaction right -> right_reaction = true, else false
    int reaction_time;          // saves the reaction time, if reaction_time = -1 there was no reaction
    // other_img other_img mid_img other_img other_img
    QString mid_img;			// saves the img in the mid - the importend arrow
    QString other_img;			// saves the img, shown arround the mid pic
    // measured?
    bool measured;              // checks if the Trial values where measured
};

#endif // TRIAL_H
