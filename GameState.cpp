//
// Created by Louis Keith on 3/1/21.
//

#include "GameState.h"

/**
 * Copy constructor.
 *
 * @param state of the board to copy
 */
GameState::GameState(const GameState &state)
{
    board = state.board;
    num_tubes = state.num_tubes;
}

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



