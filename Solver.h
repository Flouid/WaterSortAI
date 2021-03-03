//
// Created by Louis Keith on 3/1/21.
//

#ifndef WATERSORT_SOLVER_H
#define WATERSORT_SOLVER_H

#include <utility>
#include <chrono>

#include "GameState.h"

/**
 * Class representing a node on a non-binary tree of all potential games
 */
class Node {
public:
    explicit Node(const GameState &gameState) : Node(gameState, "Initialization", 0) {}
    Node(const GameState &gameState, std::string move, int dep);

    int calculate_num_valid_pours();
    bool calculate_is_game_complete() const;
    void print_state() const;

    bool populate_children();

    GameState state;
    std::vector<Node*> children;
    std::string move_description;
    int depth;
    int num_valid_pours;
    bool complete;
};

/**
 * Class tracking the root of the non-binary tree and providing a method to populate the entire tree.
 */
class Solver
{
public:
    explicit Solver(const GameState &gameState) : root(new Node(gameState)) {}

    void run();

private:
    Node* root;

    bool find_solution(Node *node, std::vector<Node*> &path);
};





#endif //WATERSORT_SOLVER_H
