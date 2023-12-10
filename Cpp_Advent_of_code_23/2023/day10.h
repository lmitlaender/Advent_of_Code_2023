#pragma once
#include "util.h"
#include "IDay.h"
#include <vector>
#include <string>
#include <algorithm>

class Day10_2023 : public IDay {
public:
    void Part1();
    void Part2();
    std::vector<std::string> input_vector;

private:
    void get_next(const char& current, std::pair<int, int>& curr,  std::pair<int, int>& prev);
    std::vector<std::pair<int, int>> get_starting_points(const std::vector<std::string>& input, std::vector<std::pair<int, int>>& prevs);
    int calculate_area(std::vector<std::pair<int, int>>& ordered_boundary_points);
};