#pragma once
#include "util.h"
#include "IDay.h"
#include <vector>
#include <string>
#include <map>

class Day8_2023 : public IDay {
public:
	void Part1();
	void Part2();
	std::vector<std::string> input_vector;

private:
	class Node
	{
	public:
		std::string id{};
		Node* left{nullptr};
		Node* right{nullptr};
	};
};