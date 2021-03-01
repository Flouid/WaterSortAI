//
// Created by Louis Keith on 3/1/21.
//

#ifndef WATERSORT_TUBE_H
#define WATERSORT_TUBE_H

#include <string>
#include <utility>
#include <vector>
#include <iostream>

class Tube
{
public:
    Tube() : Tube("Tube 0") {}
    explicit Tube(std::string tube_name) :
            Tube(std::move(tube_name), {"empty", "empty", "empty", "empty"}) {}
    Tube(std::string tube_name, std::vector<std::string> tube_values) :
            name(std::move(tube_name)), values(std::move(tube_values)) {}

    void print_tube() const;

private:
    std::vector<std::string> values;
    std::string name;
};

#endif //WATERSORT_TUBE_H
