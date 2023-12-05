#pragma once
#include "util.h"
#include "IDay.h"
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <limits>
#include <array>
#include <algorithm>

class Day5_2023 : public IDay {
public:
	void Part1();
	void Part2();
	std::vector<std::string> input_vector;
};