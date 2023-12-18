#include "day14.h"

void Day14_2023::Part1()
{
	this->input_vector = get_input("2023/Inputs/Day14.txt");

	std::set<std::pair<int, int>> immovables{};
	std::vector<std::pair<int, int>> round_rocks{};

	for(int i = 0; i < input_vector.size(); ++i)
	{
		for (int y = 0; y < input_vector[i].size(); ++y)
		{
			if (input_vector[i][y] == '#')
			{
				immovables.emplace(y, i);
			} else if(input_vector[i][y] == 'O')
			{
				round_rocks.emplace_back(y, i);
			}
		}
	}

	int total_load{};
	for (auto& rock : round_rocks)
	{
		this->slide(rock, immovables, round_rocks, { 0, -1 }); // 0, -1 stands for 0 change on x axis, -1 change on y axis, so going NORTH
		total_load += this->input_vector.size() - rock.second;
	}

	std::cout << "Part 1 Day 14: " << total_load <<  "\n";
}

void Day14_2023::Part2()
{
	this->input_vector = get_input("2023/Inputs/Day14.txt");

	std::set<std::pair<int, int>> immovables{};
	std::vector<std::pair<int, int>> round_rocks{};

	for (int i = 0; i < input_vector.size(); ++i)
	{
		for (int y = 0; y < input_vector[i].size(); ++y)
		{
			if (input_vector[i][y] == '#')
			{
				immovables.emplace(y, i);
			}
			else if (input_vector[i][y] == 'O')
			{
				round_rocks.emplace_back(y, i);
			}
		}
	}

	bool cache_hit{ false };
	int cycle_after{ 0 };

	for (int i = 0; i < 1000000000; i++)
	{
		std::string before{ this->print_thing(immovables, round_rocks) };

		if (this->cache.contains(before))
		{
			if (!cache_hit)
			{
				std::cout << "Hit cache at: " << i << "\n";
				cycle_after = i;
				cache_hit = true;
			}
			round_rocks = cache[before];
			int multiplier{ (1000000000 - i) / cycle_after };
			i *= multiplier;
			continue;
		}
		auto original_round_rocks{ round_rocks };

		for (auto& rock : round_rocks)
		{
			this->slide(rock, immovables, round_rocks, { 0, -1 }); // 0, -1 stands for 0 change on x axis, -1 change on y axis, so going NORTH
		}

		for (auto& rock : round_rocks)
		{
			this->slide(rock, immovables, round_rocks, { -1, 0 });
		}

		for (auto& rock : round_rocks)
		{
			this->slide(rock, immovables, round_rocks, { 0, 1 });
		}

		for (auto& rock : round_rocks)
		{
			this->slide(rock, immovables, round_rocks, { 1, 0 });
		}

		cache.insert({ before, round_rocks });
		//this->print_thing(immovables, round_rocks);
	}

	int total_load{};
	for (auto& rock : round_rocks)
	{
		total_load += this->input_vector.size() - rock.second;
	}

	std::cout << "Part 2 Day 14: " << total_load << "\n";
}

void Day14_2023::slide(std::pair<int, int>& pos, const std::set<std::pair<int, int>>& immovables, const std::vector<std::pair<int, int>>& rocks, const std::pair<int, int>& direction)
{
	auto immovable{ this->get_closest_immovable(pos, immovables, direction) };
	std::pair<int, int> new_pos{ immovable.first - direction.first, immovable.second - direction.second };

	while (true)
	{
		if (std::find(rocks.cbegin(), rocks.cend(), new_pos) != rocks.cend() && (new_pos.second != pos.second || new_pos.first != pos.first))
		{
			new_pos = { new_pos.first - direction.first, new_pos.second - direction.second };
			continue;
		}
		break;
	}

	pos = new_pos;
}

std::pair<int, int> Day14_2023::get_closest_immovable(const std::pair<int, int>& pos, const std::set<std::pair<int, int>>& immovables, const std::pair<int, int>& direction)
{
	double lowest_dist{ 9999999.0 };
	double dist{};
	std::pair<int, int> lowest_pair{ -1, -1 };

	for(auto& immovable : immovables)
	{
		if (direction.first == 0)
		{
			if (immovable.first != pos.first)
			{
				continue;
			}
		}
		else
		{
			if (direction.first == -1)
			{
				if (immovable.first > pos.first)
				{
					continue;
				}
			}
			else
			{
				if (immovable.first < pos.first)
				{
					continue;
				}
			}
		}

		if (direction.second == 0)
		{
			if (immovable.second != pos.second)
			{
				continue;
			}
		}
		else
		{
			if (direction.second == -1)
			{
				if (immovable.second >  pos.second)
				{
					continue;
				}
			} else
			{
				if (immovable.second < pos.second)
				{
					continue;
				}
			}
		}

		dist = std::abs(immovable.first - pos.first + immovable.second - pos.second); // one of the two parts will always be 0 because we slide in straight directions. Second part decides the distance.

		if (dist < lowest_dist)
		{
			lowest_dist = dist;
			lowest_pair = immovable;
		}
	}

	if (lowest_pair.first == -1)
	{
		if (direction.first == 1)
		{
			return { this->input_vector[0].size(), pos.second };
		}
		if (direction.first == -1)
		{
			return { -1, pos.second };
		}
		if (direction.second == 1)
		{
			return { pos.first, this->input_vector.size() };
		}
		if (direction.second == -1)
		{
			return { pos.first, -1 };
		}
	}

	return lowest_pair;
}

std::string Day14_2023::print_thing(const std::set<std::pair<int, int>>& immovables, std::vector<std::pair<int, int>>& rocks)
{
	std::vector<std::vector<char>> print_array{};

	for (auto& line : this->input_vector)
	{
		print_array.emplace_back();
		for (auto& c : line)
		{
			(print_array.end() - 1)->emplace_back('.');
		}
	}

	for (auto& immovable : immovables)
	{
		print_array[immovable.second][immovable.first] = '#';
	}

	for (auto& rock : rocks)
	{
		print_array[rock.second][rock.first] = 'O';
	}

	std::string result{};

	for (auto& line : print_array)
	{
		result.append("\n");
		for (auto& c : line)
		{
			result += c;
		}
	}

	return result;
}