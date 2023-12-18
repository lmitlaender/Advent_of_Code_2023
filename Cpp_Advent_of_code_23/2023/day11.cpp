#include "day10.h"

void Day11_2023::Part1()
{
    this->input_vector = get_input("2023/Inputs/Day11.txt");

	std::set<int> expanded_rows{};
	std::set<int> expanded_columns{};
	std::vector<std::pair<int, int>> galaxies{};
	std::set<std::pair<int, int>> already_done;

	this->find_expanded_and_galaxies(expanded_rows, expanded_columns, galaxies);

	// To find min steps it's always the diagonal. But because we never do real diagonal distance here we can just go straight up down and left right until we are at our target, which is a lot easier to calculate.

	long long total{};
	for (auto& galaxy : galaxies)
	{
		total += this->get_path_length_for_galaxy(galaxy, galaxies, expanded_rows, expanded_columns, already_done, 1);
	}

    std::cout << "Day 11 2023 Part 1: " << total << "\n";
}

void Day11_2023::Part2()
{
	this->input_vector = get_input("2023/Inputs/Day11.txt");

	std::set<int> expanded_rows{};
	std::set<int> expanded_columns{};
	std::vector<std::pair<int, int>> galaxies{};
	std::set<std::pair<int, int>> already_done;

	this->find_expanded_and_galaxies(expanded_rows, expanded_columns, galaxies);

	// To find min steps it's always the diagonal. But because we never do real diagonal distance here we can just go straight up down and left right until we are at our target, which is a lot easier to calculate.

	long long total{};
	for (auto& galaxy : galaxies)
	{
		total += this->get_path_length_for_galaxy(galaxy, galaxies, expanded_rows, expanded_columns, already_done, 999999);
	}

	std::cout << "Day 11 2023 Part 2: " << total << "\n";
}

void Day11_2023::find_expanded_and_galaxies(std::set<int>& expanded_rows, std::set<int>& expanded_columns, std::vector<std::pair<int, int>>& galaxies)
{
	for (int i = 0; i < this->input_vector.size(); i++)
	{
		if (!this->input_vector[i].contains('#'))
		{
			expanded_rows.emplace(i);
		}
		else
		{
			for (int y = 0; y < input_vector[i].size(); y++)
			{
				if (input_vector[i][y] == '#')
				{
					galaxies.emplace_back(y, i);
				}
			}
		}
	}

	for (int i = 0; i < this->input_vector[0].size(); i++)
	{
		bool empty{ true };
		for (auto& row : this->input_vector)
		{
			if (row[i] == '#')
			{
				empty = false;
				break;
			}
		}
		if (empty)
		{
			expanded_columns.emplace(i);
		}
	}
}

long long Day11_2023::get_path_length_for_galaxy(std::pair<int, int>& galaxy, std::vector<std::pair<int, int>>& galaxies, std::set<int>& expanded_rows, std::set<int>& expanded_columns, std::set<std::pair<int, int>>& already_done, int add_per_empty)
{
	long long total{};
	already_done.emplace(galaxy);

	for (auto& point : galaxies)
	{
		if (point == galaxy)
		{
			continue;
		}
		if (already_done.contains(point))
		{
			continue;
		}

		int to_add{ 0 };
		int smaller = point.first <= galaxy.first ? point.first : galaxy.first;
		int bigger = point.first > galaxy.first ? point.first : galaxy.first;

		for (int i = smaller; i < bigger; i++)
		{
			if (expanded_columns.contains(i))
			{
				to_add += add_per_empty;
			}
		}

		smaller = point.second <= galaxy.second ? point.second : galaxy.second;
		bigger = point.second > galaxy.second ? point.second : galaxy.second;

		for (int i = smaller; i < bigger; i++)
		{
			if (expanded_rows.contains(i))
			{
				to_add += add_per_empty;
			}
		}

		total += std::abs(point.first - galaxy.first) + std::abs(point.second - galaxy.second) + to_add;
	}

	return total;
}