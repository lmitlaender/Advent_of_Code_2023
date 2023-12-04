#include "day4.h"


void Day4_2023::Part1()
{
	this->input_vector = get_input("2023/Inputs/Day4.txt");

	std::string str{  };
	int total{ 0 };

	for (const auto& line : this->input_vector)
	{
		std::istringstream input_stream{ line };
		input_stream >> str >> str; //Get to the right spot (Card xy:)

		std::set<int> winners{};
		std::vector<int> numbers_on_ticket{};
		bool colon_passed{ false };
		int number{};

		while (!input_stream.eof())
		{
			input_stream >> str;

			if (str == "|")
			{
				colon_passed = true;
				continue;
			}

			number = std::stoi(str);

			if (colon_passed)
			{
				numbers_on_ticket.push_back(number);
			}
			else
			{
				winners.insert(number);
			}
		}
		int no_winners{ this->get_amount_winners(winners, numbers_on_ticket) };

		if (no_winners != 0)
		{
			total += std::pow(2, no_winners - 1);
		}
	}

	std::cout << "Day 4 2023 Part 1: " << total << "\n";
}

void Day4_2023::Part2()
{
	this->input_vector = get_input("2023/Inputs/Day4.txt");
	uint64_t len_input{ input_vector.size() };

	std::vector<int> duplicate_count;
	duplicate_count.reserve(len_input);
	for (int i = 0; i < len_input; i++)
		duplicate_count.push_back(1);

	std::string str{  };
	int total{ 0 };
	

	for (const auto& line : this->input_vector)
	{

		std::istringstream input_stream{ line };
		input_stream >> str >> str; //Get to the right spot (Card xy:)
		const int card_no{ std::stoi(str.substr(0, str.size() - 1)) };

		std::set<int> winners{};
		std::vector<int> numbers_on_ticket{};
		bool colon_passed{ false };
		int number{};

		while (!input_stream.eof())
		{
			input_stream >> str;

			if (str == "|")
			{
				colon_passed = true;
				continue;
			}

			number = std::stoi(str);

			if (colon_passed)
			{
				numbers_on_ticket.push_back(number);
			}
			else
			{
				winners.insert(number);
			}
		}

		int no_winners{ this->get_amount_winners(winners, numbers_on_ticket) };

		if (no_winners != 0)
		{
			for (int i = card_no; i < card_no + no_winners; ++i)
			{
				if(i >= len_input)
				{
					break;
				}
				duplicate_count[i] += 1 * duplicate_count[card_no - 1];
			}
		}
	}

	int sum = 0;
	sum = std::accumulate(duplicate_count.begin(), duplicate_count.end(), sum);

	std::cout << "Day 4 2023 Part 1: " << sum << "\n";
}

int Day4_2023::get_amount_winners(const std::set<int>& winners, const std::vector<int>& numbers_on_ticket)
{
	int no_found{ 0 };
	for (auto number : numbers_on_ticket)
	{
		if (winners.contains(number))
		{
			no_found++;
		}
	}
	return no_found;
}