//
// Created by Louis Keith on 3/1/21.
//

#include "Solver.h"

/**
 * Allows comparison of two nodes by ordering based on their state scores.
 *
 * @param n1 the left argument
 * @param n2 the right argument
 * @return bool representing whether or not n1's state score is less than n2's
 */
bool operator<(const Node &n1, const Node &n2) {
    return n1.state_score < n2.state_score;
}

/**
 * Detailed constructor to create a node.
 * Is given a game state, a pointer to its parent, the last move as a string, and the depth...
 * Determines the number of valid pours and whether or not the board is complete.
 *
 * @param game_state current state of the board
 * @param par pointer to the parent node
 * @param move string representing the move required to get to this state from the parent
 * @param dep integer representing the depth of the current node
 */
Node::Node(const std::vector<Tube> &game_state, std::string move, int dep)
{
    state = game_state;
    move_description = std::move(move);
    depth = dep;

    valid_pours = calculate_valid_pours();
    complete = calculate_is_game_complete();
    state_score = evaluate_state();
}

/**
 * Calculates the total number of valid pour operations for the current game state.
 * Stores them in a map indexed by an evaluation of how good each move is.
 *
 * @return multimap containing all valid pours, ordered by how good each move is
 */
std::multimap<int, std::pair<int, int>> Node::calculate_valid_pours()
{
    std::multimap<int, std::pair<int, int>> pours;
    // iterate through every source tube
    for (int i = 0; i < state.size(); ++i) {
        // iterate through every target tube
        for (int j = 0; j < state.size(); ++j) {
            // don't pour into itself
            if (i == j)
                continue;
            if (state[i].is_valid_pour(state[j]))
                pours.insert(std::pair<int, std::pair<int, int>>(evaluate_pour({i, j}), {i, j}));
        }
    }
    return pours;
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
    for (const Tube &tube: state) {
        // if the tube is full of the same color or empty, it is solved
        if (tube.get_top_color_depth() == 4 || tube.is_empty())
            ++num_solved_tubes;
    }
    return num_solved_tubes == state.size();
}

/**
 * Evaluates a pour to determine how good of a move it is. Higher scores represent theoretically better moves.
 *
 * @param pour pair representing a pair of indices in state to do a pour operation on
 * @return move score, higher is better
 */
int Node::evaluate_pour(const std::pair<int, int> &pour, int n) const
{
    // declare named variables for the source and target tubes
    int source = std::get<0>(pour);
    int target = std::get<1>(pour);
    // keep track of the heuristic score
    int score = 0;
    // create a copy of the gamestate
    std::vector<Tube> new_state = state;

    // simulate the pour
    new_state[source].pour(new_state[target]);

    // reward pours that would empty out the source tube and create an empty tube
    //score += new_state[source].is_empty();
    // reward pours that pour into a tube that is all one color
    score += new_state[target].get_top_color_depth() + new_state[target].get_free_spaces() == 4;
    // reward pours that would fill up the target tube
    score += new_state[target].get_top_color_depth() == 4;
    // reward pouring several slots at a time
    score += state[source].get_top_color_depth() - 1;
    // reward pouring into less full tubes
    score += state[target].get_free_spaces() - 1;
    // heavily penalize pouring into an empty tube
    if (state[target].is_empty())
        score -= 10;

    int source_free_spaces = state[source].get_free_spaces();
    for (int i = 0; i < state.size(); ++i) {
        if (i == source || i == target)
            continue;
        // if source wouldn't be emptied by the pour, reward pours that open up new pours
        // can only award as many points as there are spaces to pour into
        if (!new_state[source].is_empty() && source_free_spaces > 0) {
            if (new_state[i].is_valid_pour(new_state[source])) {
                ++score;
                source_free_spaces -= new_state[i].get_top_color_depth();
            }
        }
        // reward pours if there are other tubes that could also pour into the target
        score += new_state[i].is_valid_pour(new_state[target]);
    }

    return score;
}

/**
 * Return a heuristic evaluation of how good the game state is.
 *
 * @return integer representing how good the game state is
 */
int Node::evaluate_state() const
{
    // calculate the number of grouped colors across all tubes
    int num_grouped_colors = 0;
    // for each tube...
    for (const Tube &tube: state) {
        // for each value in the tube except the last...
        for (int i = 0; i < 3; ++i) {
            // increment the number of grouped colors if the color is the same as the one beneath it
            num_grouped_colors += (tube.get_values()[i] != "empty" && tube.get_values()[i] == tube.get_values()[i + 1]);
        }
    }
    // get the average move score
    int move_score_sum = 0;
    // add the move score of each move to the sum
    for (const auto & valid_pour : valid_pours) {
        move_score_sum += valid_pour.first;
    }
    int average_move_score = move_score_sum / (int)valid_pours.size();

    return num_grouped_colors + average_move_score;
}

/**
 * Populates all of the children of a node.
 * For each valid move possible, copies the gamestate to a new child node and performs that move.
 * If a move results in a completed board state, stop and return true. Otherwise, return false.
 * Performs this by heuristically guessing the best moves and exploring those paths first.
 *
 * @return bool representing whether or not the node generated children
 */
bool Node::r_populate_children()
{
    int i;
    int j;
    // goes through all of the valid pours in reverse order
    // this should populate the best moves first
    for (auto iterator = valid_pours.rbegin(); iterator != valid_pours.rend(); ++iterator) {
        i = std::get<0>(iterator->second);
        j = std::get<1>(iterator->second);
        // create a copy of the game state
        std::vector<Tube> new_state = state;
        // perform the pour on the copy
        new_state[i].pour(new_state[j]);
        // create a new node with the new game state
        std::shared_ptr<Node> new_node(new Node(new_state,
                                                std::to_string(i + 1) + " -> " + std::to_string(j + 1 ) + ":\t\t" + std::to_string(iterator->first),
                                                depth + 1));
        // insert it into the children
        children.push_back(new_node);

        // if a node is complete
        if (new_node->complete || new_node->r_populate_children())
            return true;
    }
    if (valid_pours.size() != children.size()) {
        std::cout << "Critical Error: Mismatch between number of valid pours and number of children\n";
        exit(1);
    }
    return false;
}

/**
 * Populates all of the children of a node.
 * For each valid move possible, copies the gamestate to a new child node and performs that move.
 * If a move results in a completed board state, stop and return true. Otherwise, return false.
 *
 * @return bool representing whether or not the node generated children
 */
bool Node::p_populate_children()
{
    int i;
    int j;
    // traverse the map of valid pours in reverse order, since better moves were placed further back
    for (auto iterator = valid_pours.rbegin(); iterator != valid_pours.rend(); ++iterator) {
        i = std::get<0>(iterator->second);
        j = std::get<1>(iterator->second);
        // create a copy of the game state
        std::vector<Tube> new_state = state;
        // perform the pour on the copy
        new_state[i].pour(new_state[j]);
        // create a new node with the new game state
        std::shared_ptr<Node> new_node(new Node(new_state,
                                                std::to_string(i + 1) + " -> " + std::to_string(j + 1 ) + ":\t\t" + std::to_string(iterator->first),
                                                depth + 1));
        // insert it into the children
        children.push_back(new_node);

        // if a node is complete
        if (new_node->complete)
            return true;
    }
    if (valid_pours.size() != children.size()) {
        std::cout << "Critical Error: Mismatch between number of valid pours and number of children\n";
        exit(1);
    }
    return false;
}

/**
 * Iteratively populate the tree in a level order manner. This finds a shortest possible solution.
 * VERY SLOW
 *
 * @return bool representing whether or not the tree was populated
 */
bool Solver::perfect_populate_tree() {
    if (root == nullptr)
        return false;

    // create a queue and push the root
    std::queue<std::shared_ptr<Node>> queue;
    queue.push(root);

    // track which board states have already been seen so we can skip them
    std::vector<std::vector<Tube>> states;

    // continue the core loop until every node has been processed
    while (!queue.empty()) {
        // figure out how many nodes are on this level
        int n = queue.size();

        // while there are still nodes on this level
        while (n > 0) {
            // pop the node off of the queue and populate it
            std::shared_ptr<Node> node = queue.front();
            queue.pop();
            // if the state has already been seen, decrement n and continue
            if (std::find(states.begin(), states.end(), node->state) != states.end()) {
                n--;
                continue;
            }
            states.push_back(node->state);
            // otherwise, populate it's children and stop if one of them is a solution
            if (node->p_populate_children())
                return true;

            // push all of the children onto the queue
            for (std::shared_ptr<Node> &child : node->children)
                queue.push(child);
            // a parent has been processed
            n--;
        }
    }
    return false;
}

/**
 * A totally experimental way of populating the solution tree.
 * Adds each child node to a map that is sorted by a heuristic evaluation of the game state.
 * Treat the map like a queue and always look at the last element before removing it from the map.
 *
 * @return bool representing whether or not the tree was populated
 */
bool Solver::hybrid_populate_tree() {
    if (root == nullptr)
        return false;

    // create a queue and push the root
    std::priority_queue<std::shared_ptr<Node>> queue;
    queue.push(root);

    // track which board states have already been seen so we can skip them
    std::vector<std::vector<Tube>> states;

    // continue the core loop until every node has been processed
    while (!queue.empty()) {
        // figure out how many nodes are on this level
        int n = queue.size();

        // while there are still nodes on this level
        while (n > 0) {
            // pop the node off of the queue and populate it
            std::shared_ptr<Node> node = queue.top();
            queue.pop();
            // if the state has already been seen, decrement n and continue
            if (std::find(states.begin(), states.end(), node->state) != states.end()) {
                n--;
                continue;
            }
            states.push_back(node->state);
            // otherwise, populate it's children and stop if one of them is a solution
            if (node->p_populate_children())
                return true;

            // push all of the children onto the queue
            for (std::shared_ptr<Node> &child : node->children)
                queue.push(child);
            // a parent has been processed
            n--;
        }
    }
    return false;
}

/**
 * Perform a depth-first search of the solution tree.
 * Along the way, keep track of the moves required to reach the solution.
 * Since the tree is populated left->right, search the rightmost branches first as that's where the solution should be.
 *
 * @param node pointing to the subtree to search
 * @param path vector of nodes representing the path taken
 * @return bool representing whether bool was found in the searched subtree
 */
bool Solver::find_solution(std::shared_ptr<Node> &node, std::vector<std::shared_ptr<Node>> &path)
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
    for (std::shared_ptr<Node> &child : node->children) {
        if (find_solution(child, path)) {
            return true;
        }
    }
    // if the solution was not found in any of the children, the node is not part of the path
    path.pop_back();
    return false;
}

/**
 * Traverse the tree and count how many nodes it contains.
 *
 * @param node pointer to the subtree that should be counted
 * @param n integer storing the number of nodes
 */
void Solver::count_nodes(const std::shared_ptr<Node> &node, int &n) const
{
    if (node == nullptr)
        return;
    ++n;
    for (const std::shared_ptr<Node> &child : node->children) {
        count_nodes(child, n);
    }
}

/**
 * Public wrapper function to provide users of Solver to count the number of nodes in the tree.
 *
 * @return integer representing the number of nodes found
 */
int Solver::count_nodes() const
{
    int n = 0;
    count_nodes(root, n);
    return n;
}

/**
 * Goes through each tree and prints it's move and valid number of moves.
 *
 * @param node pointer to subtree to print.
 */
void Solver::print_tree(const std::shared_ptr<Node> &node) const
{
    // special cases for null pointer
    if (node == nullptr)
        return;
    // space nodes to the right based on how deep they are
    for (int i = 0; i < node->depth; ++i) {
        printf("  ");
    }
    // print statement
    if (node == root) {
        printf("Initial Valid Moves = %lu\n", root->valid_pours.size());
    }
    else {
        printf("%s:  %lu", node->move_description.c_str(), node->valid_pours.size());
        if (node->complete)
            printf(" !!!!!\n");
        else
            printf("\n");
    }
    // recursive calls
    for(const std::shared_ptr<Node> &child : node->children) {
        print_tree(child);
    }
}

/**
 * Public wrapper function to print the contents of an entire tree.
 */
void Solver::print_tree() const
{
    std::cout << std::endl;
    print_tree(root);
    std::cout << std::endl;
}

/**
 * Wrapper function to populate the tree, find the solution, and print the path to the solution found.
 */
void Solver::run(char mode)
{
    // time tracking done within this function, locally use this namespace for readability
    using namespace std::chrono;

    // populate the tree and measure how long it takes.
    auto start_pop = high_resolution_clock::now();
    switch(mode) {
        case 'f':
            root->r_populate_children();
            break;
        case 'p':
            perfect_populate_tree();
            break;
        case 'h':
            hybrid_populate_tree();
            break;
        default:
            exit(1);
    }
    auto stop_pop = high_resolution_clock::now();
    auto duration_to_populate_tree = duration_cast<microseconds>(stop_pop - start_pop);

    // find the path to the solution
    auto start_find = high_resolution_clock::now();
    std::vector<std::shared_ptr<Node>> path;
    if (!find_solution(root, path))
        std::cout << "There was an error, could not find path to solution\n";
    auto stop_find = high_resolution_clock::now();
    auto duration_to_find_solution = duration_cast<microseconds>(stop_find - start_find);

    // print out the entire tree
    print_tree();

    // print the path to the solution
    std::cout << "Path to solution:\n";
    for (int i = 0; i < path.size(); ++i) {
        printf("[%d]:\t%s\n", i, path[i]->move_description.c_str());
    }
    printf("\nTime required to populate the solution tree:\t%lld microseconds\n", duration_to_populate_tree.count());
    printf("Time required to find the solution in the tree:\t%lld microseconds\n", duration_to_find_solution.count());
    printf("The generated tree had %d nodes\n", count_nodes());
}

/**
 * Wrapper function to perform average execution time test on a gamestate
 *
 * @param repetitions int representing the number of repetitions to average across
 */
void Solver::r_time_test(int repetitions)
{
    using namespace std::chrono;

    double total_population_duration = 0;
    double total_find_duration = 0;

    // populate the tree several times to measure the average runtime
    for (int i = 0; i < repetitions; ++i) {
        // if this isn't the first loop, the tree is already populated
        if (!root->children.empty()) {
            // reset the root node
            root = std::shared_ptr<Node>(new Node(root->state));
        }

        // populate the tree and measure how long it takes.
        auto start_pop = high_resolution_clock::now();
        // if the user chooses to perform a deep solve, it calculates breadth first for the shortest possible solution
        if (!root->r_populate_children())
            std::cout << "There was an error, no solution found\n";
        auto stop_pop = high_resolution_clock::now();
        total_population_duration += duration_cast<microseconds>(stop_pop - start_pop).count();

        // find the path to the solution
        auto start_find = high_resolution_clock::now();
        std::vector<std::shared_ptr<Node>> path;
        if (!find_solution(root, path))
            std::cout << "There was an error, could not find path to solution\n";
        auto stop_find = high_resolution_clock::now();
        total_find_duration += duration_cast<microseconds>(stop_find - start_find).count();
    }

    printf("It took on average %.0f microseconds to populate the tree.\n", total_population_duration/repetitions);
    printf("It took on average %.0f microseconds to find the solution in the tree.\n", total_find_duration/repetitions);
}