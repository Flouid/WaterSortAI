//
// Created by Louis Keith on 3/1/21.
//

#include "GameState.h"

/**
 * Print the state of the game state.
 */
void GameState::print_board() const
{
    printf("Board State:\tNumber of Tubes = %d\n", num_tubes);
    for(const Tube &tube: board) {
        std::cout << tube;
    }
    std::cout << std::endl;
}
