#include "day12.h"

void Day12_2023::Part1()
{
	this->input_vector = get_input("2023/Inputs/Day12.txt");

	long long total{};
	for (auto& line : input_vector)
	{
		std::istringstream string_stream{ line };
		std::string spring{};
		string_stream >> spring;
		spring += ".";
		std::map<std::pair<int, int>, long long> cache{};

		std::string group_string{};
		string_stream >> group_string;

		std::vector<int> groups{};

		while(true)
		{
			auto pos = group_string.find(',');
			groups.push_back(std::stoi(group_string.substr(0, pos)));

			if (pos == std::string::npos)
			{
				break;
			}

			group_string = group_string.substr(pos + 1);
		}

		total += this->count(spring, groups, 0, 0, cache);
	}
	std::cout << "Part 1 Day 12 (cheated, but I understood finally (can I blame covid for my brain not working and reading the task)): " << total << "\n";
}

void Day12_2023::Part2()
{
	this->input_vector = get_input("2023/Inputs/Day12.txt");

	long long total{};
	for (auto& line : input_vector)
	{
		std::istringstream string_stream{ line };
		std::string spring{};
		string_stream >> spring;
		spring += "?" + spring + "?" + spring + "?" + spring + "?" + spring;

		spring += ".";
		std::map<std::pair<int, int>, long long> cache{};

		std::string group_string{};
		string_stream >> group_string;
		group_string += "," + group_string + "," + group_string + "," + group_string + "," + group_string;

		std::vector<int> groups{};

		while (true)
		{
			auto pos = group_string.find(',');
			groups.push_back(std::stoi(group_string.substr(0, pos)));

			if (pos == std::string::npos)
			{
				break;
			}

			group_string = group_string.substr(pos + 1);
		}

		total += this->count(spring, groups, 0, 0, cache);
	}

	std::cout << "Part 2 Day 12 (cheated, but I understood): " << total << "\n";
}


long long Day12_2023::count(std::string spring, std::vector<int> groups, int pattern_idx, int count_idx, std::map<std::pair<int, int>, long long>& cache)
{
	std::pair key{ pattern_idx, count_idx };
	if (cache.contains(key))
	{
		return cache[key];
	}

	if (pattern_idx >= spring.length())
	{
		return count_idx == groups.size() ? 1 : 0;
	}

	long long permutations{};

	char curr_char{ spring[pattern_idx] };

	if (curr_char != '#') // it's either . or ? so this is the case, where it is .
	{
		permutations += this->count(spring, groups, pattern_idx + 1, count_idx, cache);
	}

	if (curr_char != '.' && count_idx < groups.size()) // So either # or ? that would be the ? = # case
	{
		bool can_consume{ true };
		int needs{ groups[count_idx] - 1 };
		while (can_consume && needs > 0)
		{
			pattern_idx++;
			needs--;
			can_consume = pattern_idx < spring.length() && spring[pattern_idx] != '.';
		}

		if (can_consume)
		{
			int seperator_idx{ pattern_idx + 1 };
			if (seperator_idx >= spring.length() || spring[seperator_idx] != '#')
			{
				permutations += this->count(spring, groups, seperator_idx + 1, count_idx + 1, cache);
			}
		}
	}

	cache.insert(std::pair{ key, permutations });
	return permutations;
}


/*bool can_place_here(std::string_view pattern, int damaged) {
	if (pattern[damaged] == '#') return false;
	for (int i = 0; i < damaged; ++i) {
		if (pattern[i] == '.') return false;
	}
	return true;
}

long long Day12_2023::count(std::string spring, std::vector<int> groups)
{
	if (groups.empty())
	{
		return std::find(spring.begin(), spring.end(), '#') == spring.end();
	}

	int group{ groups[0] };
	
	if (spring.length() <= group)
	{
		return 0; // Not valid
	}

	long long permutations{};

	// Valid cases
	std::vector<int> new_group{ groups.begin() + 1, groups.end() };

	bool placed{ false };
	if (can_place_here(spring, group)){
		placed = true;
		permutations += this->count(spring.substr(group + 1), new_group);
	}

	if (spring[0] == '#') return permutations;

	permutations += this->count(spring.substr(1), groups);
	return permutations;
}*/