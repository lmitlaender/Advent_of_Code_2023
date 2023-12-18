#pragma once
#include "util.h"
#include "IDay.h"
#include <vector>
#include <string>
#include <numeric>

class Day12_2023 : public IDay {
public:
    void Part1();
    void Part2();
    std::vector<std::string> input_vector;

private:
    long long count(std::string spring, std::vector<int> groups, int pattern_idx, int count_idx, std::map<std::pair<int, int>, long long>& cache);
};