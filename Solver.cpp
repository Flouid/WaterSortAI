//
// Created by Louis Keith on 3/1/21.
//

#include "Solver.h"

/**
 * Calculates the total number of valid pour operations for the current game state
 *
 * @return int representing total number of valid pours
 */
int Solver::get_num_valid_pours()
{
    int valid_pours = 0;
    // iterate through every source tube
    for (int i = 0; i < state.get_num_tubes(); ++i) {
        // iterate through every target tube
        for (int j = 0; j < state.get_num_tubes(); ++j) {
            // don't pour into itself
            if (i == j) {
                continue;
            }
            valid_pours += state.board[i].is_valid_pour(state.board[j]);
        }
    }
    return valid_pours;
}

/**
 * Iterates through every tube in the game state and determines if they are all sorted.
 * If every tube is either full of the same color or empty, the game is complete.
 *
 * @return bool representing whether or not the game is complete
 */
bool Solver::is_game_complete() const
{
    int num_solved_tubes = 0;
    // iterate through every tube
    for (const Tube &tube: state.board) {
        // if the tube is full of the same color or empty, it is solved
        if (tube.get_top_color_depth() == 4 || tube.is_empty())
            ++num_solved_tubes;
    }
    return num_solved_tubes == state.get_num_tubes();
}