//
// Created by Louis Keith on 3/1/21.
//

#ifndef WATERSORT_SOLVER_H
#define WATERSORT_SOLVER_H

#include <utility>

#include "GameState.h"

/**
 * Class representing a node on a non-binary tree of all potential games
 */
class Node {
public:
    explicit Node(GameState gameState) : Node(std::move(gameState), nullptr, "Initialization") {}
    Node(GameState gameState, Node* par, std::string move);

    int get_num_valid_pours();
    bool is_game_complete() const;
    void print_state() const;

    GameState state;
    Node* parent;
    std::vector<Node*> children;
    std::string move_description;

    int num_valid_pours;
    bool complete;
};

class Solver
{
public:
    explicit Solver(GameState gameState) : root(new Node(std::move(gameState))) {}

    Node* root;
};





#endif //WATERSORT_SOLVER_H
