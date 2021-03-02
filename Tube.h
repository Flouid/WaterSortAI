//
// Created by Louis Keith on 3/1/21.
//

#ifndef WATERSORT_TUBE_H
#define WATERSORT_TUBE_H

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <cassert>

class Tube
{
public:
    Tube() : Tube("Tube 0") {}
    explicit Tube(std::string tube_name) : Tube(std::move(tube_name),{"empty", "empty", "empty", "empty"}) {}
    Tube(std::string tube_name, std::vector<std::string> tube_values);

    void print_tube() const;

private:
    std::vector<std::string> values;
    std::string name;
    int free_spaces;
    int top_color_depth;

    bool is_valid() const;
    int calculate_free_spaces();
    int calculate_top_color_depth();
};

#endif //WATERSORT_TUBE_H
