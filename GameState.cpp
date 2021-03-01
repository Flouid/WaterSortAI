//
// Created by Louis Keith on 3/1/21.
//

#include "GameState.h"

void GameState::add_tube(const Tube &tube)
{
    board.push_back(tube);
    ++num_tubes;
}

void GameState::init_board()
{
    std::string name_1 = "Tube " + std::to_string(num_tubes + 1);
    std::string name_2 = "Tube " + std::to_string(num_tubes + 2);

    add_tube(Tube(name_1));
    add_tube(Tube(name_2));
}

void GameState::print_board() const
{
    for(const Tube &tube: board) {
        tube.print_tube();
    }
    std::cout << std::endl << "There are " << num_tubes << " tubes" << std::endl;
}

