//
// Created by Louis Keith on 3/1/21.
//

#ifndef WATERSORT_SOLVER_H
#define WATERSORT_SOLVER_H

#include <utility>
#include <chrono>
#include <queue>

#include "Tube.h"

/**
 * Class representing a node on a non-binary tree of all potential games
 */
class Node {
public:
    explicit Node(const std::vector<Tube> &tubes) : Node(tubes, "Initialization", 0) {}
    Node(const std::vector<Tube> &game_state, std::string move, int dep);

    std::vector<std::tuple<int, int>> calculate_valid_pours();
    bool calculate_is_game_complete() const;

    bool populate_children();

    std::vector<Tube> state;
    std::vector<std::shared_ptr<Node>> children;
    std::vector<std::tuple<int, int>> valid_pours;
    std::string move_description;
    int depth;
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
    void time_test(int repetitions = 25);
    int count_nodes() const;
    void print_tree() const;

private:
    std::shared_ptr<Node> root;

    bool find_solution(std::shared_ptr<Node> &node, std::vector<std::shared_ptr<Node>> &path);
    void count_nodes(const std::shared_ptr<Node> &node, int &n) const;
    void print_tree(const std::shared_ptr<Node> &node) const;
    bool populate();
};

#endif //WATERSORT_SOLVER_H
