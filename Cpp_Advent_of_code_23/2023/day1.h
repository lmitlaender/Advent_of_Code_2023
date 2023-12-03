#pragma once
#include "util.h"
#include "IDay.h"
#include <vector>
#include <string>
#include <map>
#include <regex>

class Day1_2023 : public IDay {
public:
	void Part1();
	void Part2();
	std::string map_to_number(std::string number_as_string);
	std::vector<std::string> input_vector;

	std::map<std::string, std::string> string_to_number_string{
		{"one", "1"},
		{"two", "2"},
		{"three", "3"},
		{"four", "4"},
		{"five", "5"},
		{"six", "6"},
		{"seven", "7"},
		{"eight", "8"},
		{"nine", "9"}
	};
};