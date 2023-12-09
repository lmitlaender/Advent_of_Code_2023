#pragma once
#include "util.h"
#include "IDay.h"
#include <vector>
#include <string>
#include <sstream>

class Day9_2023 : public IDay {
public:
	void Part1();
	void Part2();
	std::vector<std::string> input_vector;

private:
	int get_next(std::vector<int>& vec, bool forward);
};
