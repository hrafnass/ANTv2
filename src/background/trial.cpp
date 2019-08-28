#include "trial.h"

Trial::Trial(star_position star_posi, arrow_position arrow_posi, image img1)
{
    star_pos = star_posi;
    arrow_pos = arrow_posi;
    img = img1;
    right_reaction = false;         // a false reaction is the start value
    reaction_time = -1;             // no reaction is the start value
    setDirection();                 // set the direction after setting img
    setImg();                       // set the images
}

// public methods
// setter
void Trial::setReactionTime(int time){ reaction_time = time; }
void Trial::setRightReaction(bool reaction){ right_reaction = reaction; }
// getter
// measured values
bool Trial::getRightReaction() { return right_reaction; }
int Trial::getReactionTime() { return reaction_time; }
// image postions
Trial::star_position Trial::getStarPosition() { return star_pos; }
Trial::arrow_position Trial::getArrowPosition() { return arrow_pos; }
Trial::dir Trial::getDirection(){ return direction;}
// getter for mid and other image (arrows)
QString Trial::getMidImg() { return mid_img; }
QString Trial::getOtherImg() { return other_img; }

// private method
// setter
void Trial::setDirection(){
    // the first 3 pictures have this mid arrow: <-, the other ->
    if(img < 3)
        direction = dir::l;
    else
        direction = dir::r;
}

// setter img
// the most images doesn't exist yet
void Trial::setImg(){
    switch(img){
        case image::lllll:
            mid_img = ":/ressources/images/arrow_left.svg";
            other_img = ":/ressources/images/arrow_left.svg";
            break;
        case image::llrll:
            mid_img = ":/ressources/images/arrow_right.svg";
            other_img = ":/ressources/images/arrow_left.svg";
            break;
        case image::rrlrr:
            mid_img = ":/ressources/images/arrow_left.svg";
            other_img = ":/ressources/images/arrow_right.svg";
            break;
        case image::rrrrr:
            mid_img = ":/ressources/images/arrow_right.svg";
            other_img = ":/ressources/images/arrow_right.svg";
            break;
        case image::sslss:
            mid_img = ":ressources/images/arrow_left.svg";
            other_img = ":ressources/images/bar.svg";
            break;
        case image::ssrss:
            mid_img = ":/ressources/images/arrow_right.svg";
            other_img = ":/ressources/images/bar.svg";
            break;
        default:
                return;
    }
}
