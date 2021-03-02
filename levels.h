//
// Created by Louis Keith on 3/1/21.
//

#ifndef WATERSORT_LEVELS_H
#define WATERSORT_LEVELS_H

#include "GameState.h"
#include "Solver.h"

void invalid_tube();
void pour_test(const Tube& t1, const Tube &t2);
void num_valid_pours_test(const GameState &state);
void is_game_complete_test(const GameState &state);
void l1();
void l2();
void l3();

#endif //WATERSORT_LEVELS_H
