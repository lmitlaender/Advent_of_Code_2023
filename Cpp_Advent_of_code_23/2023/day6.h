#pragma once
#include "util.h"
#include "IDay.h"
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

class Day6_2023 : public IDay {
public:
	void Part1();
	void Part2();
	std::vector<std::string> input_vector;
};