//
// Created by Louis Keith on 3/1/21.
//

#include "levels.h"

void invalid_tube()
{
    Tube t1("Tube 1", {"green", "blue", "black", "empty"});

    GameState board;
    board.add_tube(t1);

    board.print_board();
}

void l1()
{
    Tube t1("Tube 1", {"empty", "empty", "empty", "orange"});
    Tube t2("Tube 2", {"empty", "orange", "orange", "orange"});

    GameState board;
    board.add_tube(t1);
    board.add_tube(t2);

    board.print_board();
}

void l2()
{
     Tube t1("Tube 1", {"orange", "dark blue", "orange", "dark blue"});
     Tube t2("Tube 2", {"dark blue", "orange", "dark blue", "orange"});
     Tube t3("Tube 3");

     GameState board;
     board.add_tube(t1);
     board.add_tube(t2);
     board.add_tube(t3);

     board.print_board();
}

void l3()
{
    Tube t1("Tube 1", {"dark blue", "red", "orange", "dark blue"});
    Tube t2("Tube 2", {"dark blue", "red", "orange", "orange"});
    Tube t3("Tube 3", {"red", "orange", "dark blue", "red"});

    GameState board;
    board.add_tube(t1);
    board.add_tube(t2);
    board.add_tube(t3);
    board.init_board();

    board.print_board();
}