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

void pour_test(const Tube &t1, const Tube &t2) {
    std::vector<Tube> tubes;
    tubes.push_back(t1);
    tubes.push_back(t2);

    GameState board(tubes);
    board.print_board();

    bool worked = board.board[0].pour(board.board[1]);
    printf("Pour Success: %d\n", worked);
    board.print_board();
}

void node_test(const GameState &state)
{
    Node node(state);
    node.print_state();
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