#pragma once
#include "util.h"
#include "IDay.h"
#include <vector>
#include <string>

class Day16_2023 : public IDay {
public:
    void Part1();
    void Part2();
    std::vector<std::string> input_vector;

private:
    struct beam
    {
        std::pair<int, int> direction;
        std::pair<int, int> position;
    };

    void move_step(beam& beam_to_move, std::vector<beam>& beams);
    void print_thing(std::set<std::pair<int, int>>& visited);
    int wrapper(std::pair<int, int> direction, std::pair<int, int> start_pos);
};