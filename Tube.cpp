//
// Created by Louis Keith on 3/1/21.
//

#include "Tube.h"

/**
 * Detailed constructor for initializing a tube.
 *
 * @param tube_name
 * @param tube_values
 */
Tube::Tube(std::string tube_name, std::vector<std::string> tube_values) : name(std::move(tube_name)), values(std::move(tube_values))
{
    if (!is_valid()) {
        // if the tube isn't valid, exit immediately and notify the user.
        std::cout << "Assertion failed, invalid tube" << std::endl;
        assert(is_valid());
    }
    free_spaces = calculate_free_spaces();
    top_color_depth = calculate_top_color_depth();
}

/**
 * Checks if a tube is valid. That is, no empty slots beneath a filled one.
 *
 * @return boolean representing if the tube is valid or not.
 */
bool Tube::is_valid() const
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
 * Calculates how many slots from the top down are free.
 *
 * @return int representing how many free spaces the tube has.
 */
int Tube::calculate_free_spaces()
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
int Tube::calculate_top_color_depth()
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
 * Prints all of the data associated with a tube to the console.
 */
void Tube::print_tube() const
{
    std::cout << '\t' << name << ':' << "\tFree Spaces: " << free_spaces <<
                 "\tTop Color Depth: " << top_color_depth << std::endl;
    for(const std::string &value: values) {
        std::cout << "\t\t" << value << std::endl;
    }
    std::cout << std::endl;
}
