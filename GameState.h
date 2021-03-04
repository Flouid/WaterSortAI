//
// Created by Louis Keith on 3/1/21.
//

#ifndef WATERSORT_GAMESTATE_H
#define WATERSORT_GAMESTATE_H

#include <utility>

#include "Tube.h"

/**
 * Class representing the current state of a given board.
 * Has methods for initializing, adding tubes, and printing the board.
 */
class GameState
{
public:
    GameState() : num_tubes(0) {}
    explicit GameState(std::vector<Tube> tubes) : board(std::move(tubes)), num_tubes(board.size()) {}
    GameState(const GameState &state);

    void print_board() const;
    int get_num_tubes() const {return num_tubes;}

    std::vector<Tube> board;

private:
    int num_tubes;
};

#endif //WATERSORT_GAMESTATE_H
