#pragma once
#include "util.h"
#include "IDay.h"
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <string>
#include <string_view>

class Day2_2023 : public IDay {
public:
	void Part1();
	void Part2();
	std::string map_to_number(const std::string& number_as_string);
	std::vector<std::string> input_vector;

private:
	std::unordered_map<std::string, int> limits{
		{"red", 12},
		{"green", 13},
		{"blue", 14}
	};
};
