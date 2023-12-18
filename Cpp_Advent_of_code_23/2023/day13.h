#pragma once
#include "util.h"
#include "IDay.h"
#include <vector>
#include <string>

class Day13_2023 : public IDay {
public:
    void Part1();
    void Part2();
    std::vector<std::string> input_vector;

private:
    int get_result_for_block(std::vector<std::string>& block, std::set<int>& column_candidates, std::set<int>& row_candidates);
    std::pair<int, int> get_valid_candidate(std::vector<std::string>& block);
};