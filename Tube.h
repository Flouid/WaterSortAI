//
// Created by Louis Keith on 3/1/21.
//

#ifndef WATERSORT_TUBE_H
#define WATERSORT_TUBE_H

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <fstream>

/**
 * A data type representing a tube in the game WaterSort.
 * Each tube has four slots that can contain a color or be empty.
 * Colors "fall" within the tube so there cannot be empty slots beneath a full one.
 */
class Tube
{
public:
    friend std::ostream & operator<<(std::ostream &out, const Tube &t);
    friend std::istream & operator>>(std::istream &in, Tube &t);
    friend bool operator==(const Tube &t1, const Tube &t2);

    Tube() : Tube({"empty", "empty", "empty", "empty"}) {}
    explicit Tube(std::vector<std::string> tube_values);

    void pour(Tube &target);
    bool is_valid_pour(Tube &target) const;

    bool is_empty() const { return empty; }
    int get_free_spaces() const { return free_spaces; }
    int get_top_color_depth() const { return top_color_depth; }

private:
    std::vector<std::string> values;
    std::string top_color;
    bool empty;
    int free_spaces;
    int top_color_depth;

    bool calculate_is_valid() const;
    bool calculate_is_empty() const;
    int calculate_free_spaces() const;
    int calculate_top_color_depth() const;
    std::string calculate_top_color() const;
};

#endif //WATERSORT_TUBE_H
