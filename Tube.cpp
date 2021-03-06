//
// Created by Louis Keith on 3/1/21.
//

#include "Tube.h"

/**
 * Output operator for a tube. Provides all of the functionality expected from an output stream.
 * Primarily for debugging.
 *
 * @param out output stream
 * @param t tube to output
 * @return output stream
 */
std::ostream & operator<<(std::ostream &out, const Tube &t)
{
    printf("\tTube:\tFree Spaces = %d,\tTop Color Depth = %d,\tTop Color = %s,\tIs Empty = %d\n",
           t.free_spaces, t.top_color_depth, t.top_color.c_str(), t.empty);
    for(const std::string &value: t.values) {
        std::cout << "\t\t" << value << std::endl;
    }
    std::cout << std::endl;

    return out;
}

/**
 * Input operator for a tube. Provides all of the functionality expected from an input stream.
 * Primarily for reading from file input.
 *
 * @param in input stream
 * @param t tube to read into
 * @return input stream
 */
std::istream & operator>>(std::istream &in, Tube &t)
{
    std::vector<std::string> values;
    std::string value;

    // read four color values
    for (int i = 0; i < 4; ++i) {
        in >> value;
        // the logic requires that empty slots be explicitly marked "empty", but "e" should be a valid input
        if (value == "e")
            value = "empty";
        values.push_back(value);
    }

    // set data for the tube
    t.values = values;
    t.top_color = t.calculate_top_color();
    t.empty = t.calculate_is_empty();
    t.free_spaces = t.calculate_free_spaces();
    t.top_color_depth = t.calculate_top_color_depth();

    return in;
}

/**
 * Overloaded equals operator to compare two tubes.
 * Used in the perfect solver algorithm to track visited states.
 *
 * @param t1 Tube representing the left argument
 * @param t2 Tube representing the right argument
 * @return boolean representing equality
 */
bool operator==(const Tube &t1, const Tube &t2)
{
    return t1.values == t2.values;
}

/**
 * Detailed constructor for initializing a tube.
 * Takes a vector of color values as argument.
 *
 * @param tube_values vector of string representing the value in each slot
 */
Tube::Tube(std::vector<std::string> tube_values) : values(std::move(tube_values))
{
    if (!calculate_is_valid()) {
        // if the tube isn't valid, exit immediately and notify the user.
        std::cout << "Assertion failed, invalid tube" << std::endl;
        assert(calculate_is_valid());
    }

    free_spaces = calculate_free_spaces();
    top_color_depth = calculate_top_color_depth();
    empty = calculate_is_empty();
    top_color = calculate_top_color();
}

/**
 * Checks if a tube is valid. That is, there are no empty slots beneath a filled one.
 *
 * @return boolean representing if the tube is valid or not.
 */
bool Tube::calculate_is_valid() const
{
    // checks the bottom of the tube. If empty, everything above must also be empty
    if(this->values[3] == "empty") {
        if(this->values[2] != "empty" || this->values[1] != "empty" || this->values[0] != "empty")
            return false;
    }
    // checks the second slot from the bottom of the tube. If empty, everything above must also be empty
    else if(this->values[2] == "empty") {
        if(this->values[1] != "empty" || this->values[0] != "empty")
            return false;
    }
    // checks the second slot from the top of the tube. If empty, the top slot must also be empty.
    else if(this->values[1] == "empty") {
        if(this->values[0] != "empty")
            return false;
    }
    return true;
}

/**
 * Checks if a tube is completely empty.
 *
 * @return bool representing whether or not the tube is empty.
 */
bool Tube::calculate_is_empty() const
{
    return std::all_of(values.begin(), values.end(),
                    [](const std::string &value){return value == "empty";});
}

/**
 * Calculates how many slots from the top down are free.
 *
 * @return int representing how many free spaces the tube has.
 */
int Tube::calculate_free_spaces() const
{
    int free_slots = 0;
    // iterates over all slots and counts how many are empty
    for (const std::string &value: values) {
        if(value == "empty")
            ++free_slots;
    }
    return free_slots;
}

/**
 * Calculates how "deep" the color on the top is.
 *
 * @return int representing how many slots from the top are filled with the same color.
 */
int Tube::calculate_top_color_depth() const
{
    std::string color;
    bool color_set = false;
    int color_depth = 0;
    // iterates over all slots...
    for (const std::string &value: values) {
        // if there is a color here and the top color isn't set, set color and count it
        if(value != "empty" && !color_set) {
            color = value;
            color_set = true;
            ++color_depth;
        }
        // if value is equal to the top color, increment the depth counter
        else if(value == color) {
            ++color_depth;
        }
        // if the top color is set and value isn't that color, the loop is complete
        else if(value != color && color_set) {
            break;
        }
    }
    return color_depth;
}

/**
 * Gets the color at the top of the tube.
 *
 * @return string representing the color at the top of the tube.
 */
std::string Tube::calculate_top_color() const
{
    std::string top;
    bool top_color_set = false;
    // iterate through every color, if the value isn't empty then it's the top color.
    for (const std::string &value: values) {
        if (value != "empty") {
            top = value;
            top_color_set = true;
            break;
        }
    }
    // if all of the values were empty and the color wasn't set, set it to empty.
    if (!top_color_set) {
        top = "empty";
    }
    return top;
}

/**
 * Performs a "pour" operation from the current source tube into another target tube.
 * Pours are only to be performed if the operation has been deemed valid by is_valid_pour().
 * Follows all of the rules given in the game WaterSort:
 *  1. Target must be empty or the tubes must share a top color
 *  2. Target tube must not be full
 *  3. Can only pour as many slots as there are free spaces in the target
 *  4. Source tube must not be empty
 *
 * @param target tube to pour into
 */
void Tube::pour(Tube &target)
{
    // find the index in the target tube of the deepest empty slot
    int deepest_empty_slot;
    // set the original pour color
    std::string pour_color = top_color;

    // iterate through every slot in the source tube...
    for (int i = 0; i < 4; ++i) {
        // skip empty slots
        if (values[i] == "empty")
            continue;
        // starting at the deepest empty slot, fill upward
        deepest_empty_slot = target.free_spaces - 1;
        // if the top color hasn't changed...
        if (top_color == pour_color) {
            target.values[deepest_empty_slot] = top_color;
            values[i] = "empty";
            top_color = calculate_top_color();
            ++free_spaces;
            --target.free_spaces;
            // exit condition for the loop, pour is complete
            if(target.free_spaces == 0) {
                break;
            }
        }
        // no more of that color to pour
        else {
            break;
        }
    }
    // recalculate some data for both tubes
    empty = calculate_is_empty();
    target.empty = target.calculate_is_empty();
    top_color_depth = calculate_top_color_depth();
    target.top_color_depth = target.calculate_top_color_depth();
    target.top_color = target.calculate_top_color();
}

/**
 * Checks if pouring to target is possible.
 * Moves that cannot contribute to a better board state are found to be invalid.
 * Moves are valid if:
 *  1. The source is not empty
 *  2. The target has free spaces
 *  3. The top colors of the source and target are the same or the target is empty
 * Moves that cannot contribute:
 *  1. The target is empty and the source is all one color
 *  2. It's impossible to pour all of the top color into the target
 *
 * @param target tube
 * @return bool representing whether or not a pour is possible
 */
bool Tube::is_valid_pour(Tube &target) const
{
    if (empty || target.free_spaces == 0 || (top_color != target.top_color && !target.empty))
        return false;

    // if the source tube has only one color in it and the target is empty, forbid the move as it can't contribute
    bool all_one_color = 4 - top_color_depth == free_spaces;
    if (all_one_color && target.is_empty())
        return false;

    // if it's not possible to pour all of the top color out, don't
    if (top_color_depth > target.free_spaces)
        return false;

    return true;
}
