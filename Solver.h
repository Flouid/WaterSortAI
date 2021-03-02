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
    explicit Solver(GameState gameState) : state(std::move(gameState)) {}

    int get_num_valid_pours();
    bool is_game_complete() const;

private:
    GameState state;
};

#endif //WATERSORT_SOLVER_H
