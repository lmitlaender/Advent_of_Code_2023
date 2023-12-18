#pragma once
#include "util.h"
#include "IDay.h"
#include <vector>
#include <string>

class Day14_2023 : public IDay {
public:
    void Part1();
    void Part2();
    std::vector<std::string> input_vector;

private:
    void slide(std::pair<int, int>& pos, const std::set<std::pair<int, int>>& immovables, const std::vector<std::pair<int, int>>& rocks, const std::pair<int, int>& direction);
    std::pair<int, int> get_closest_immovable(const std::pair<int, int>& pos, const std::set<std::pair<int, int>>& immovables, const std::pair<int, int>& direction);
    std::string print_thing(const std::set<std::pair<int, int>>& immovables, std::vector<std::pair<int, int>>& rocks);
    std::unordered_map<std::string, std::vector<std::pair<int, int>>> cache;
};