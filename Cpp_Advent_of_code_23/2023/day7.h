#pragma once
#include "util.h"
#include "IDay.h"
#include <vector>
#include <string>
#include <set>
#include <map>
#include <fstream>

class Day7_2023 : public IDay {
public:
	void Part1();
	void Part2();
	std::vector<std::string> input_vector;
	enum hand_type{HIGH, PAIR, TWO_PAIR, THREE_OF_A_KIND, FULL_HOUSE, FOUR_OF_A_KIND, FIVE_OF_A_KIND};
	static bool hand_comparator(const std::string& hand1, const std::string& hand2);

private:
	hand_type get_hand_type(const std::string& hand);
	hand_type get_hand_type_wrapper(const std::string& hand);
};