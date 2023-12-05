#include "day5.h"

void Day5_2023::Part1()
{
	this->input_vector = get_input("2023/Inputs/Day5.txt");

	std::vector<std::vector<std::array<long long, 3>>> range_table;
	int current_map_index{ -1 };

	std::vector<long long> seeds{};
	std::string str{};
	std::istringstream strstream{ input_vector[0] };

	strstream >> str;

	while (!strstream.eof())
	{
		strstream >> str;
		seeds.push_back(std::stoll(str));
	}

	for(int i = 2; i < input_vector.size(); i++)
	{
		if (std::isblank(input_vector[i][0]))
		{
			continue;
		} else if (!isdigit(input_vector[i][0]))
		{
			range_table.emplace_back();
			current_map_index++;
			continue;
		}

		// first destination_start, second source_start, third length of range
		std::istringstream map_stream{ input_vector[i] };

		map_stream >> str;
		const long long destination_start{ std::stoll(str) };

		map_stream >> str;
		const long long source_start{ std::stoll(str) };

		map_stream >> str;
		const long long length{ std::stoll(str) };

		range_table[current_map_index].push_back(std::array<long long, 3>{source_start, destination_start, length});
	}

	long long lowest{ std::numeric_limits<long long>::max() };
	for (const auto seed : seeds)
	{
		long long mapped_value{ seed };
		for (auto& mapping_vector : range_table)
		{
			for (auto& range : mapping_vector)
			{
				if (mapped_value >= range[0] && mapped_value < range[0] + range[2])
				{
					long long offset{ mapped_value - range[0]};
					mapped_value = range[1] + offset;
					break;
				}
			}
		}
		if (mapped_value < lowest)
			lowest = mapped_value;
	}

	std::cout << "Day 5 2023 Part 1: " << lowest << "\n";
}


void Day5_2023::Part2()
{
	this->input_vector = get_input("2023/Inputs/Day5.txt");

	long long lowest{ std::numeric_limits<long long>::max() };

	std::vector<std::vector<std::array<long long, 3>>> range_table;
	int current_map_index{ -1 };

	std::vector<long long> seeds{};
	std::string str{};
	std::istringstream strstream{ input_vector[0] };

	strstream >> str;

	while (!strstream.eof())
	{
		strstream >> str;
		seeds.push_back(std::stoll(str));
	}

	for (int i = 2; i < input_vector.size(); i++)
	{
		if (input_vector[i].empty())
		{
			continue;
		}
		else if (!isdigit(input_vector[i][0]))
		{
			range_table.emplace_back();
			current_map_index++;
			continue;
		}

		// first destination_start, second source_start, third length of range
		std::istringstream map_stream{ input_vector[i] };

		map_stream >> str;
		const long long destination_start{ std::stoll(str) };

		map_stream >> str;
		const long long source_start{ std::stoll(str) };

		map_stream >> str;
		const long long length{ std::stoll(str) };

		range_table[current_map_index].push_back(std::array<long long, 3>{source_start, destination_start, length});
	}

	
	bool seed_found{ false };
	long long lowest_location{ 0 };
	std::reverse(range_table.begin(), range_table.end());
	// going backwards
	while (!seed_found)
	{
		long long mapped_value{ lowest_location };
		for (auto& mapping_vector : range_table)
		{
			for (auto& range : mapping_vector)
			{
				if (mapped_value >= range[1] && mapped_value < range[1] + range[2])
				{
					long long offset{ mapped_value - range[1] };
					mapped_value = range[0] + offset;
					break;
				}
			}
		}
		for (int i = 0; i < seeds.size(); i += 2)
		{
			if (mapped_value >= seeds[i] && mapped_value < seeds[i] + seeds[i + 1])
			{
				seed_found = true;
				lowest = lowest_location;
				break;
			}
		}
		lowest_location++;
	}

	// Alternative more algorithmic solution
	// Credits to gitpushjoe for the idea, and then my ugly implementation I wrote down rushedly without any thinking

	/*long long lowest2{ std::numeric_limits<long long>::max() };
	for (long long i = 0; i < seeds.size(); i += 2)
	{
		for (long long seed = seeds[i]; seed < seeds[i] + seeds[i + 1]; )
		{
			long long range_to_skip = { -1 };
			long long mapped_value{ seed };
			for (auto& mapping_vector : range_table)
			{	
				bool mapping_found{ false };
				for (auto& range : mapping_vector)
				{
					if (mapped_value >= range[0] && mapped_value < range[0] + range[2])
					{
						long long offset{ mapped_value - range[0] };
						long long range_to_max = range[0] + range[2] - 1 - mapped_value;
						mapped_value = range[1] + offset;
						if (range_to_skip == -1 || range_to_max < range_to_skip)
							range_to_skip = range_to_max;
						mapping_found = true;
						break;
					}
				}
				if (!mapping_found) {
					long long range_to_max{ -1 };
					for (auto& mapping : mapping_vector)
					{
						long long range_to_start = mapping[0] - mapped_value - 1;
						if ((range_to_start < range_to_max || range_to_max == -1) && range_to_start >= 0)
						{
							range_to_max = range_to_start;
						}
					}
					if (range_to_max == -1)
						range_to_max = 9999999999;
					if (range_to_skip == -1 || range_to_max < range_to_skip)
					{
						range_to_skip = range_to_max;
					}
				}
			}
			if (mapped_value < lowest2)
				lowest2 = mapped_value;
			seed += range_to_skip;
			if (range_to_skip <= 0)
				seed++;
		}
	}
	
	std::cout << "Day 5 2023 Part 1: " << lowest2 << "\n";*/

	std::cout << "Day 5 2023 Part 1: " << lowest << "\n";
}
