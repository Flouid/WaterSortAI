//
// Created by Louis Keith on 3/1/21.
//

#ifndef WATERSORT_SOLVER_H
#define WATERSORT_SOLVER_H

#include <utility>
#include <chrono>

#include "Tube.h"

/**
 * Class representing a node on a non-binary tree of all potential games
 */
class Node {
public:
    explicit Node(const std::vector<Tube> &tubes) : Node(tubes, "Initialization", 0) {}
    Node(const std::vector<Tube> &tubes, std::string move, int dep);

    int calculate_num_valid_pours();
    bool calculate_is_game_complete() const;

    bool populate_children();

    std::vector<Tube> state;
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
    explicit Solver(const std::vector<Tube> &state) : root(new Node(state)) {}

    void run();
    int count_nodes() const;
    void print_tree() const;

private:
    Node* root;

    bool find_solution(Node *node, std::vector<Node*> &path);
    void count_nodes(const Node *node, int &n) const;
    void print_tree(const Node *node) const;
};

#endif //WATERSORT_SOLVER_H
