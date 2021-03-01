//
// Created by Louis Keith on 3/1/21.
//

#ifndef WATERSORT_GAMESTATE_H
#define WATERSORT_GAMESTATE_H

#include "Tube.h"

class GameState
{
public:
    GameState() : num_tubes(0) {}

    void add_tube(const Tube &tube);
    void init_board();
    void print_board() const;

    int get_num_tubes() {return num_tubes;};

private:
    std::vector<Tube> board;
    int num_tubes;
};

#endif //WATERSORT_GAMESTATE_H
