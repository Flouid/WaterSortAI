//
// Created by Louis Keith on 3/1/21.
//

#include "Solver.h"

/**
 * Detailed constructor to create a node.
 * Is given a game state, a pointer to its parent, the last move as a string, and the depth...
 * Determines the number of valid pours and whether or not the board is complete.
 *
 * @param gameState current state of the board
 * @param par pointer to the parent node
 * @param move string representing the move required to get to this state from the parent
 * @param dep integer representing the depth of the current node
 */
Node::Node(const GameState& gameState, Node* par, std::string move, int dep)
{
    state = gameState;
    parent = par;
    move_description = std::move(move);
    depth = dep;

    num_valid_pours = get_num_valid_pours();
    complete = is_game_complete();
}

/**
 * Calculates the total number of valid pour operations for the current game state
 *
 * @return int representing total number of valid pours
 */
int Node::get_num_valid_pours()
{
    int valid_pours = 0;
    // iterate through every source tube
    for (int i = 0; i < state.get_num_tubes(); ++i) {
        // iterate through every target tube
        for (int j = 0; j < state.get_num_tubes(); ++j) {
            // don't pour into itself
            if (i == j)
                continue;
            valid_pours += state.board[i].is_valid_pour(state.board[j]);
        }
    }
    return valid_pours;
}

/**
 * Iterates through every tube in the game state and determines if they are all sorted.
 * If every tube is either full of the same color or empty, the game is complete.
 *
 * @return bool representing whether or not the game is complete
 */
bool Node::is_game_complete() const
{
    int num_solved_tubes = 0;
    // iterate through every tube
    for (const Tube &tube: state.board) {
        // if the tube is full of the same color or empty, it is solved
        if (tube.get_top_color_depth() == 4 || tube.is_empty())
            ++num_solved_tubes;
    }
    return num_solved_tubes == state.get_num_tubes();
}

/**
 * Populates all of the children of a node.
 * For each valid move possible, copies the gamestate to a new child node and performs that move.
 * If a move results in a completed board state, stop and return true. Otherwise, return false.
 *
 * @return bool representing whether or not a child node was found.
 */
bool Node::populate_children()
{
    Node *node;
    // iterate through every source tube
    for (int i = 0; i < state.get_num_tubes(); ++i) {
        // iterate through every target tube
        for (int j = 0; j < state.get_num_tubes(); ++j) {
            // don't attempt to pour into itself
            if (i == j)
                continue;
            // if there is a valid pour...
            if (state.board[i].is_valid_pour(state.board[j])) {
                // create a copy of the board state
                node = new Node(*this);
                // perform the pour on the copy
                node->state.board[i].pour(node->state.board[j]);
                // recalculate values related to the state of the node
                node->complete = node->is_game_complete();
                node->num_valid_pours = node->get_num_valid_pours();
                node->depth++;
                node->move_description = "Poured Tube " + std::to_string(i) + " into Tube " + std::to_string(j) + ".";
                // link it to the parent (this node)
                node->parent = this;
                // insert it into the children
                children.push_back(node);

                node->print_state();

                // if a complete board state is found, no need to calculate more children.
                if (node->complete) {
                    return true;
                }
                // if the node can not proceed, this branch is done.
                else if (node->num_valid_pours == 0) {
                    return false;
                }
                else if (node->populate_children()) {
                    return true;
                }
            }
        }
    }
    // ensure there wasn't an error. Stop program execution if there was.
    if (children.size() != num_valid_pours) {
        std::cout << "Critical Error! Number of children mismatch number of valid moves\n";
        assert(children.size() == num_valid_pours);
    }
    return false;
}

bool Solver::populate_tree() const
{
    root->print_state();

    bool return_value = root->populate_children();

    return return_value;
}

/**
 * Prints the entire state of the node.
 */
void Node::print_state() const
{
    printf("Move to get here: %s\n", move_description.c_str());
    printf("Game complete = %d,\tValid moves = %d,\tDepth = %d\n", complete, num_valid_pours, depth);
    state.print_board();
}