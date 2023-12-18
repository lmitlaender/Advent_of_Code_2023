#pragma once
#include "util.h"
#include "IDay.h"
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>

class Day17_2023 : public IDay {
public:
    void Part1();
    void Part2();
    std::vector<std::string> input_vector;

private:
    struct node
    {
        int cost;
        std::pair<int, int> direction;
        int repeated_moves;
        int x;
        int y;

        bool operator == (const node& state) const {
            return state.direction.first == direction.first && state.direction.second == direction.second && state.repeated_moves == repeated_moves && state.x == x && state.y == y;
        }
    };

    struct node_comparator
    {
	    bool operator()(const node& n1, const node& n2) const
	    {
            return n1.cost > n2.cost;
	    }
    };

    void print_thing(std::vector<node>& visited);
    int dijkstra_for_pos(std::priority_queue<node, std::vector<node>, node_comparator>& queue);
    int dijkstra_for_pos_part_2(std::priority_queue<node, std::vector<node>, node_comparator>& queue);
};