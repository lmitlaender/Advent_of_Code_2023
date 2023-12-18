#include "day16.h"

void Day16_2023::Part1()
{
	this->input_vector = get_input("2023/Inputs/Day16.txt");

	std::cout << this->wrapper({1, 0}, {0, 0}) << "\n";
}

void Day16_2023::Part2()
{
	this->input_vector = get_input("2023/Inputs/Day16.txt");

	int largest{ 0 };
	int placeholder{};
	for (int i = 0; i < input_vector.size(); ++i)
	{
		std::cout << "Round: " << i << "\n";
		placeholder = this->wrapper({ 1, 0 }, { 0, i });
		if (largest < placeholder)
		{
			largest = placeholder;
		}

		placeholder = this->wrapper({ -1, 0 }, { input_vector[i].size() - 1, i});
		if (largest < placeholder)
		{
			largest = placeholder;
		}
	}

	for (int i = 0; i < input_vector[0].size(); ++i)
	{
		std::cout << "Round: " << i << "\n";
		placeholder = this->wrapper({ 0, 1 }, { i, 0 });
		if (largest < placeholder)
		{
			largest = placeholder;
		}

		placeholder = this->wrapper({ 0, -1 }, { i, input_vector.size() - 1 });
		if (largest < placeholder)
		{
			largest = placeholder;
		}
	}

	std::cout << largest << "\n";
}

int Day16_2023::wrapper(std::pair<int, int> direction, std::pair<int, int> start_pos)
{
	std::vector<beam> beams{};
	beam first_beam{ {direction}, {start_pos} };
	std::set<std::pair<int, int>> visited{};
	std::set<std::pair<std::pair<int, int>, std::pair<int, int>>> beam_happened_before{};

	beams.push_back(first_beam);
	size_t last_visited{ visited.size() };
	size_t beams_before;

	while (!beams.empty())
	{
		for (auto& beam : beams)
		{
			beam_happened_before.emplace(std::pair{ beam.direction }, std::pair{ beam.position });
		}

		beams_before = { beams.size() };
		for (int i = 0; i < beams_before; ++i)
		{
			visited.emplace(beams[i].position);
			this->move_step(beams[i], beams);
		}

		//this->print_thing(visited);
		//std::cout << "\n\n";

		std::erase_if(beams, [this, beam_happened_before](const auto& beam)
			{
				return beam.position.first < 0 || beam.position.first >= input_vector[0].size() ||
					beam.position.second < 0 || beam.position.second >= input_vector.size() || beam_happened_before.contains({ {beam.direction}, {beam.position} });
			});
	}
	return visited.size();
}

void Day16_2023::move_step(beam& beam_to_move, std::vector<beam>& beams)
{
	beam split_beam{{0, 0}, {-1, -1}};

	switch(this->input_vector[beam_to_move.position.second][beam_to_move.position.first])
	{
	case '.':
		
		break;
	case '\\':
		std::swap(beam_to_move.direction.first, beam_to_move.direction.second);
		break;
	case '/':
		std::swap(beam_to_move.direction.first, beam_to_move.direction.second);
		beam_to_move.direction.first = -beam_to_move.direction.first;
		beam_to_move.direction.second = -beam_to_move.direction.second;
		break;

	case '-':
		if (beam_to_move.direction.second != 0)
		{
			beam_to_move.direction = { 1, 0 };
			split_beam.position = beam_to_move.position;
			split_beam.direction = { -1, 0 };
		}
		break;

	case '|':
		if (beam_to_move.direction.first != 0)
		{
			beam_to_move.direction = { 0, 1 };
			split_beam.position = beam_to_move.position;
			split_beam.direction = { 0, -1 };
		}
		break;
	}

	beam_to_move.position.first += beam_to_move.direction.first;
	beam_to_move.position.second += beam_to_move.direction.second;
	if (split_beam.position.first != -1)
	{
		split_beam.position.first += split_beam.direction.first;
		split_beam.position.second += split_beam.direction.second;
		beams.push_back(split_beam);
	}
}

void Day16_2023::print_thing(std::set<std::pair<int, int>>& visited)
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

	for (auto& point : visited)
	{
		print_array[point.second][point.first] = '#';
	}

	std::string result{};

	for (auto& line : print_array)
	{
		std::cout << "\n";
		for (auto& c : line)
		{
			std::cout << c;
		}
	}
}