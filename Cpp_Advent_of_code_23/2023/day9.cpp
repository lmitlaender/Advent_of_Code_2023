#include "day9.h"

void Day9_2023::Part1()
{
	this->input_vector = get_input("2023/Inputs/Day9.txt");
	int total{};

	for (auto& line : input_vector)
	{
		std::istringstream string_stream{ line };
		std::string str;
		std::vector<int> line_vector{};

		while(!string_stream.eof())
		{
			string_stream >> str;
			line_vector.emplace_back(std::stoi(str));
		}

		total += this->get_next(line_vector, true);
	}

	std::cout << "Day 9 2023 Part 1: " << total << " sum\n";
}

void Day9_2023::Part2()
{
	this->input_vector = get_input("2023/Inputs/Day9.txt");
	int total{};

	for (auto& line : input_vector)
	{
		std::istringstream string_stream{ line };
		std::string str;
		std::vector<int> line_vector{};

		while (!string_stream.eof())
		{
			string_stream >> str;
			line_vector.emplace_back(std::stoi(str));
		}

		total += this->get_next(line_vector, false);
	}

	std::cout << "Day 9 2023 Part 2: " << total << " sum\n";
}

int Day9_2023::get_next(std::vector<int>& vec, bool forward)
{
	if (vec.size() <= 1)
	{
		return 0;
	}

	bool all_zero{ vec[0] == 0 ? true : false };
	std::vector<int> differences{};

	for (int i = 1; i < vec.size(); i++)
	{
		if (all_zero && vec[i] != 0)
		{
			all_zero = false;
		}
		differences.emplace_back(vec[i] - vec[i - 1]);
	}

	if (all_zero)
	{
		return 0;
	} else
	{
		auto next_value = this->get_next(differences, forward);

		if (forward)
		{
			return next_value + vec[vec.size() - 1];
		}
		return -next_value + vec[0];
	}
}