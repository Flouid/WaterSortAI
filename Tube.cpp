//
// Created by Louis Keith on 3/1/21.
//

#include "Tube.h"

void Tube::print_tube() const
{
    std::cout << name << ':' << std::endl;
    for(const std::string &value: values) {
        std::cout << "\t" << value << std::endl;
    }
    std::cout << std::endl;
}
