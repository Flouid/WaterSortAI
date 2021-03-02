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

void invalid_pour_source_empty()
{
    std::vector<Tube> tubes;
    tubes.emplace_back("Tube 1");
    tubes.emplace_back("Tube 2");

    GameState board(tubes);
    board.print_board();

    bool worked = board.board[0].pour(board.board[1]);
    printf("Pour Success: %d\n", worked);
    board.print_board();
}

void invalid_pour_different_colors()
{
    std::vector<Tube> tubes;
    tubes.push_back(Tube("Tube 1", {"empty", "empty", "dark blue", "red"}));
    tubes.push_back(Tube("Tube 2", {"empty", "empty", "red", "dark blue"}));

    GameState board(tubes);
    board.print_board();

    bool worked = board.board[0].pour(board.board[1]);
    printf("Pour Success: %d\n", worked);
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