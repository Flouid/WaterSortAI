//
// Created by Louis Keith on 3/1/21.
//

#include "levels.h"

void invalid_tube_init()
{
    Tube t1("Tube 1", {"green", "blue", "black", "empty"});
    GameState board;
    board.add_tube(t1);
    board.print_board();
}

void pour_overflow()
{
    GameState state({Tube("Tube 0", {"empty", "orange", "orange", "orange"}),
                     Tube("Tube 1", {"empty", "orange", "dark blue", "red"})});
    Solver solver(state);
    solver.populate_tree();
}

void l1()
{
    GameState state_l1(
            {Tube("Tube 0", {"empty", "empty", "empty", "orange"}),
             Tube("Tube 1", {"empty", "orange", "orange", "orange"})});
    Solver solver_l1(state_l1);
    if(solver_l1.populate_tree())
        std::cout << "Solution found\n";
    else
        std::cout << "Solution not found\n";
}

void l2()
{
    GameState state_l2(
            {Tube("Tube 0", {"orange", "dark blue", "orange", "dark blue"}),
             Tube("Tube 1", {"dark blue", "orange", "dark blue", "orange"}),
             Tube("Tube 2")});
    Solver solver_l2(state_l2);
    if(solver_l2.populate_tree())
        std::cout << "Solution found\n";
    else
        std::cout << "Solution not found\n";
}

void l3()
{
    GameState state_l3(
            {Tube("Tube 0", {"dark blue", "red", "orange", "dark blue"}),
             Tube("Tube 1", {"dark blue", "red", "orange", "orange"}),
             Tube("Tube 2", {"red", "orange", "dark blue", "red"})});
    state_l3.init_board();
    Solver solver_l3(state_l3);
    if(solver_l3.populate_tree())
        std::cout << "Solution found\n";
    else
        std::cout << "Solution not found\n";
}