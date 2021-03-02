//
// Created by Louis Keith on 3/1/21.
//

#include "Tube.h"

// takes name and values as arguments and initializes tube
Tube::Tube(std::string tube_name, std::vector<std::string> tube_values) : name(std::move(tube_name)), values(std::move(tube_values))
{
    if (!is_valid()) {
        std::cout << "Assertion failed, invalid tube" << std::endl;
        assert(is_valid());
    }
    free_spaces = calculate_free_spaces();
    top_color_depth = calculate_top_color_depth();
}

bool Tube::is_valid() const
{
    if(this->values[3] == "empty") {
        if(this->values[2] != "empty" || this->values[1] != "empty" || this->values[0] != "empty")
            return false;
    }
    else if(this->values[2] == "empty") {
        if(this->values[1] != "empty" || this->values[0] != "empty")
            return false;
    }
    else if(this->values[1] == "empty") {
        if(this->values[0] != "empty")
            return false;
    }
    return true;
}

int Tube::calculate_free_spaces()
{
    int free_slots = 0;
    for (const std::string &value: values) {
        if(value == "empty")
            ++free_slots;
    }
    return free_slots;
}

int Tube::calculate_top_color_depth()
{
    std::string color;
    bool color_set = false;
    int color_depth = 0;
    for (const std::string &value: values) {
        if(value != "empty" && !color_set) {
            color = value;
            color_set = true;
            ++color_depth;
        }
        else if(value == color) {
            ++color_depth;
        }
        else if(value != color && color_set) {
            break;
        }
    }
    return color_depth;
}

void Tube::print_tube() const
{
    std::cout << '\t' << name << ':' << "\tFree Spaces: " << free_spaces <<
                 "\tTop Color Depth: " << top_color_depth << std::endl;
    for(const std::string &value: values) {
        std::cout << "\t\t" << value << std::endl;
    }
    std::cout << std::endl;
}
