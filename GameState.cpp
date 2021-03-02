//
// Created by Louis Keith on 3/1/21.
//

#include "GameState.h"

/**
 * Add a tube to the game state
 *
 * @param tube
 */
void GameState::add_tube(const Tube &tube)
{
    board.push_back(tube);
    ++num_tubes;
}

/**
 * Add the two empty tubes that are included with the majority of levels.
 */
void GameState::init_board()
{
    std::string name_1 = "Tube " + std::to_string(num_tubes);
    std::string name_2 = "Tube " + std::to_string(num_tubes + 1);

    add_tube(Tube(name_1));
    add_tube(Tube(name_2));
}

/**
 * Print the state of the game state.
 */
void GameState::print_board() const
{
    std::cout << "Board State:\n";
    for(const Tube &tube: board) {
        tube.print_tube();
    }
    std::cout << "There are " << num_tubes << " tubes\n\n";
}



