//
// Created by Louis Keith on 3/1/21.
//

#include "levels.h"

void l1()
{
    Tube t1("Tube 1", {"empty", "empty", "empty", "pink"});
    Tube t2("Tube 2", {"empty", "pink", "pink", "pink"});

    GameState board;
    board.add_tube(t1);
    board.add_tube(t2);

    board.print_board();
}

void invalid_tube()
{
    Tube t1("Tube 1", {"green", "blue", "black", "empty"});

    GameState board;
    board.add_tube(t1);

    board.print_board();
}