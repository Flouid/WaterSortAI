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
Node::Node(const GameState& gameState, std::string move, int dep)
{
    state = gameState;
    move_description = std::move(move);
    depth = dep;

    num_valid_pours = calculate_num_valid_pours();
    complete = calculate_is_game_complete();
}

/**
 * Calculates the total number of valid pour operations for the current game state
 *
 * @return int representing total number of valid pours
 */
int Node::calculate_num_valid_pours()
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
bool Node::calculate_is_game_complete() const
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
                node->complete = node->calculate_is_game_complete();
                node->num_valid_pours = node->calculate_num_valid_pours();
                node->depth++;
                node->move_description = std::to_string(i + 1) + " -> " + std::to_string(j + 1);
                // insert it into the children
                children.push_back(node);

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
    // there are no solutions possible from this board state
    return false;
}

/**
 * Prints the entire state of the node.
 * Exists primarily for debugging reasons.
 */
void Node::print_state() const
{
    printf("Move to get here: %s\n", move_description.c_str());
    printf("Game complete = %d,\tValid moves = %d,\tDepth = %d\n", complete, num_valid_pours, depth);
    state.print_board();
}

/**
 * Perform a postorder depth-first search of the solution tree.
 * Along the way, keep track of the moves required to reach the solution.
 * Perform it in postorder since the tree is populated left->right,
 * meaning the solution should be all the way to the right.
 *
 * @param node pointing to the subtree to search
 * @param path vector of nodes representing the path taken
 * @return bool representing whether bool was found in the searched subtree
 */
bool Solver::find_solution(Node *node, std::vector<Node*> &path)
{
    // If the node empty, stop here
    if (node == nullptr)
        return false;
    // since the node is a candidate for the correct path, add it
    path.push_back(node);
    // if the given node is a complete board state, solution found and return
    if (node->complete)
        return true;
    // if any of the node's children is a complete board state, return true
    // search the children from right to left, as the solution should be the rightmost path in the tree
    for (unsigned long i = node->children.size() - 1; i >= 0; --i) {
        if (find_solution(node->children[i], path)) {
            return true;
        }
    }
    // if the solution was not found in any of the children, the node is not part of the path
    path.pop_back();
    return false;
}

/**
 * Wrapper function to populate the tree, find the solution, and print the path to the solution found.
 */
void Solver::run()
{
    // time tracking done within this function, locally use this namespace for readability
    using namespace std::chrono;

    // populate the tree and measure how long it takes.
    auto start_pop = high_resolution_clock::now();
    if (!root->populate_children())
        std::cout << "There was an error, no solution found\n";
    auto stop_pop = high_resolution_clock::now();
    auto duration_to_populate_tree = duration_cast<microseconds>(stop_pop - start_pop);

    // find the path to the solution
    auto start_find = high_resolution_clock::now();
    std::vector<Node*> path;
    if (!find_solution(root, path))
        std::cout << "There was an error, could not find path to solution\n";
    auto stop_find = high_resolution_clock::now();
    auto duration_to_find_solution = duration_cast<microseconds>(stop_find - start_find);

    // print the path to the solution
    for (int i = 0; i < path.size(); ++i) {
        printf("[%d]:\t%s\n", i, path[i]->move_description.c_str());
    }
    printf("\nTime required to populate the solution tree:\t%lld microseconds\n", duration_to_populate_tree.count());
    printf("Time required to find the solution in the tree:\t%lld microseconds\n", duration_to_find_solution.count());
}

