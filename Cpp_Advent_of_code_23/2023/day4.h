#pragma once
#include "util.h"
#include "IDay.h"
#include <vector>
#include <string>
#include <fstream>
#include <set>
#include <numeric>
#include <cmath>

class Day4_2023 : public IDay {
public:
	void Part1();
	void Part2();
	std::vector<std::string> input_vector;
private:
	int get_amount_winners(const std::set<int>& winners, const std::vector<int>& numbers_on_ticket);
};
