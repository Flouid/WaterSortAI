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
    bool pour(Tube &target);

private:
    std::vector<std::string> values;
    std::string name;
    bool empty;
    int free_spaces;
    int top_color_depth;
    std::string top_color;

    bool is_valid() const;
    bool is_empty() const;
    int calculate_free_spaces() const;
    int calculate_top_color_depth() const;
    std::string get_top_color() const;
};

#endif //WATERSORT_TUBE_H
