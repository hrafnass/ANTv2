/* ANTv2
 * This file is part of ANTv2.
 * 
 * ANTv2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Foobar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * 
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <https://www.gnu.org/licenses/>.
 */


#ifndef GAME_AND_GUI_DEF_H
#define GAME_AND_GUI_DEF_H

// TIMES
// waiting times in ther game
#define TIME_BETWEEN_ARROWS 1000    // in ms
#define TIME_FOR_REACTION   2000    // in ms

// SPACER DISTANCE IN CM
#define DISTANCE_ARROW_PLUS_Y 2     // its the fixed distance of a spacer - we use 2.54  at the moment
#define DISTANCE_ARROW_PLUS_X 2     // its the fixed distance of a spacer - we use 2.54  at the moment

#define NBR_OF_RUNS_TEST 1
#define NBR_OF_RUNS_GAME 2          // one run = 96 Trials

#define TRIALS_IN_RUN_GAME 96       // number of Trials in one Run - standard (for a game)
#define TRIALS_IN_RUN_TEST  6       // number of Trials in a Test Runs - standard

#define TEST        true            // for the test game setter
#define NO_TEST     false

#endif // GAME_AND_GUI_DEF_H
