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
    free_spaces = 0;
    for (const std::string &value: values) {
        if(value == "empty")
            ++free_spaces;
    }
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

void Tube::print_tube() const
{
    std::cout << name << ':' << std::endl;
    for(const std::string &value: values) {
        std::cout << "\t" << value << std::endl;
    }
    std::cout << std::endl;
}
