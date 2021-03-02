//
// Created by Louis Keith on 3/1/21.
//

#ifndef WATERSORT_SOLVER_H
#define WATERSORT_SOLVER_H

#include <utility>

#include "GameState.h"

class Solver
{
public:
    Solver(GameState gameState) : board(std::move(gameState)) {}

    int get_num_valid_pours();

private:
    GameState board;
};

#endif //WATERSORT_SOLVER_H
