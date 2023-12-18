#pragma once
#include "util.h"
#include "IDay.h"
#include <vector>
#include <string>

class Day11_2023 : public IDay {
public:
    void Part1();
    void Part2();
    std::vector<std::string> input_vector;

private:
    void find_expanded_and_galaxies(std::set<int>& expanded_rows, std::set<int>& expanded_columns, std::vector<std::pair<int, int>>& galaxies);
    long long get_path_length_for_galaxy(std::pair<int, int>& galaxy, std::vector<std::pair<int, int>>& galaxies, std::set<int>& expanded_rows, std::set<int>& expanded_columns, std::set<std::pair<int, int>>& already_done, int add_per_empty);
};