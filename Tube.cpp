//
// Created by Louis Keith on 3/1/21.
//

#include "Tube.h"

/**
 * Output operator for a tube, makes it easy to do i/o with them
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
 * Input operator for a tube, makes it easy to do i/o with them.
 * Assumes tubes are formatted as four values separated by whitespace.
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
 *
 * @param tube_name
 * @param tube_values
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
 * Checks if a tube is valid. That is, no empty slots beneath a filled one.
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
    if (std::all_of(values.begin(), values.end(),
                    [](const std::string &value){return value == "empty";}))
        return true;
    else
        return false;
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
 * Attempts to "pour" the current tube into a target tube.
 * Can only be successful if the target is empty or the two tubes share top colors.
 * If they share top colors, only pour as many slots as the target has free spaces.
 *
 * @param target tube to pour into
 * @return bool representing whether or not the operation was successful.
 */
bool Tube::pour(Tube &target)
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
    return true;
}

/**
 * Checks if pouring to target is possible.
 * It is only possible if the source isn't empty, the target has at least one free space,
 * and the top colors match or the target is empty.
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
