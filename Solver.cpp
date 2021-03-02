//
// Created by Louis Keith on 3/1/21.
//

#include "Solver.h"

int Solver::get_num_valid_pours()
{
    int valid_pours = 0;
    // iterate through every source tube
    for (int i = 0; i < board.get_num_tubes(); ++i) {
        // iterate through every target tube
        for (int j = 0; j < board.get_num_tubes(); ++j) {
            // don't pour into itself
            if (i == j) {
                continue;
            }
            valid_pours += board.board[i].is_valid_pour(board.board[j]);
        }
    }
    return valid_pours;
}