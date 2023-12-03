#pragma once
#include "util.h"
#include "IDay.h"
#include <vector>
#include <string>
#include <regex>
#include <map>
#include <set>
#include <tuple>

class Day3_2023 : public IDay {
public:
	void Part1();
	void Part2();
	std::vector<std::string> input_vector;

private:
	bool check_match(const int& line_no,const int match_pos,const int match_length);
	static bool is_symbol(const char& c);
	std::map<std::tuple<int, int>, int> digit_at{};

};
