//
// Created by Louis Keith on 3/1/21.
//

#ifndef WATERSORT_SOLVER_H
#define WATERSORT_SOLVER_H

#include <utility>
#include <chrono>
#include <queue>
#include <map>

#include "Tube.h"

/**
 * struct representing a node on a non-binary solution tree of all potential games.
 *
 * Tracks the current game state, any child game states, a collection of valid pours,
 * a description of the last move, the depth of the current node, and a flag representing
 * whether or not the game is complete.
 */
struct Node {
    explicit Node(const std::vector<Tube> &tubes) : Node(tubes, "Initialization", 0) {}
    Node(const std::vector<Tube> &game_state, const std::string &move, int dep);

    std::multimap<int, std::pair<int, int>> calculate_valid_pours();
    bool calculate_is_game_complete() const;
    int evaluate_pour(const std::pair<int, int> &pour) const;

    bool r_populate_children();
    bool p_populate_children();

    std::vector<Tube> state;
    std::vector<std::shared_ptr<Node>> children;
    std::multimap<int, std::pair<int, int>> valid_pours;
    std::string move_description;
    int depth;
    bool complete;
};

/**
 * Class tracking the root of the non-binary solution tree and providing a method to run the analysis.
 */
class Solver
{
public:
    explicit Solver(const std::vector<Tube> &state) : root(new Node(state)) {}

    void run(char mode);
    int count_nodes() const;
    void print_tree() const;

private:
    std::shared_ptr<Node> root;

    bool find_solution(std::shared_ptr<Node> &node, std::vector<std::shared_ptr<Node>> &path);
    void count_nodes(const std::shared_ptr<Node> &node, int &n) const;
    void print_tree(const std::shared_ptr<Node> &node) const;
    bool perfect_populate_tree();
};

#endif //WATERSORT_SOLVER_H
