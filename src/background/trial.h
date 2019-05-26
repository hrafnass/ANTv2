#ifndef TRIAL_H
#define TRIAL_H
#include <QString>
#include <vector>

using namespace std;

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
};

#endif // TRIAL_H
