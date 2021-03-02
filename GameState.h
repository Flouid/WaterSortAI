//
// Created by Louis Keith on 3/1/21.
//

#ifndef WATERSORT_GAMESTATE_H
#define WATERSORT_GAMESTATE_H

#include <utility>

#include "Tube.h"

class GameState
{
public:
    GameState() : num_tubes(0) {}
    GameState(std::vector<Tube> tubes) : board(std::move(tubes)), num_tubes(board.size()) {}

    void add_tube(const Tube &tube);
    void init_board();
    void print_board() const;

    int get_num_tubes() {return num_tubes;}

    std::vector<Tube> board;

private:
    int num_tubes;
};

#endif //WATERSORT_GAMESTATE_H
