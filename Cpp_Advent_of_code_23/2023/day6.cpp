#include "day6.h"

void Day6_2023::Part1()
{
	this->input_vector = get_input("2023/Inputs/Day6.txt");

	// We have a function of the form distance < x * (time - x)
	// Which expands to distance < -x^2 + time * x
	// Take time -1 => -distance < x^2 - time*x
	// Which we can expand with time*time/4 on both sides to get a binominal solution to get -distance + (time * time / 4) < (x - time/2)^2
	// Then squareroot = sqrt(-distance + (time * time / 4)) < x - time/2
	// and finally sqrt(-distance + (time * time / 4)) + time/2 < x and sqrt(-distance + (time * time / 4)) - time/2 < x
	// which we can use to find the zero points which help us figure out all the options to win per time distance pair.

	std::vector<double> time{};
	std::vector<double> distance{};
	bool second_line{ false };

	for (auto& line : input_vector)
	{
		std::string str{};
		std::istringstream string_stream{line};
		string_stream >> str;
		while (!string_stream.eof())
		{
			string_stream >> str;

			if(!second_line)
			{
				time.push_back(std::stod(str));
			}else
			{
				distance.push_back(std::stod(str));
			}
		}
		second_line = true;
	}

	int total{1};

	for(int i = 0; i < time.size(); i++)
	{
		const double x1 = std::sqrt(-distance[i] + ((time[i] * time[i]) / 4)) + time[i] / 2;
		const double x2 = -1 * (std::sqrt(-distance[i] + ((time[i] * time[i]) / 4)) - time[i] / 2);

		const int from{ static_cast<int>(x2 + 1) };
		const int to{ static_cast<int>(x1 - 0.00000000000001) };
		const int ways_to_win{ to - from + 1 };

		total *= ways_to_win;

		std::cout << "Value x1: " << x1 << "; Value x2: " << x2 << "; Time: " << time[i] << "; Distance: " << distance[i] << "; Ways to win: " << ways_to_win << "\n";
	}

	std::cout << "\nDay 6 2023 Part 1: " << total << "\n\n\n";
}


void Day6_2023::Part2()
{
	this->input_vector = get_input("2023/Inputs/Day6.txt");

	// We have a function of the form distance < x * (time - x)
	// Which expands to distance < -x^2 + time * x
	// Take time -1 => -distance < x^2 - time*x
	// Which we can expand with time*time/4 on both sides to get a binominal solution to get -distance + (time * time / 4) < (x - time/2)^2
	// Then squareroot = sqrt(-distance + (time * time / 4)) < x - time/2
	// and finally sqrt(-distance + (time * time / 4)) + time/2 < x and sqrt(-distance + (time * time / 4)) - time/2 < x
	// which we can use to find the zero points which help us figure out all the options to win per time distance pair.

	double time{};
	double distance{};
	bool second_line{ false };

	for (auto& line : input_vector)
	{
		std::string str{};
		std::string complete_string{};
		std::istringstream string_stream{ line };
		string_stream >> str;
		while (!string_stream.eof())
		{
			string_stream >> str;
			complete_string += str;
		}

		if (!second_line)
		{
			time = std::stod(complete_string);
		}
		else
		{
			distance = std::stod(complete_string);
		}
		second_line = true;
	}

	const double x1 = std::sqrt(-distance + ((time * time) / 4)) + time / 2;
	const double x2 = -1 * (std::sqrt(-distance + ((time * time) / 4)) - time / 2);

	const long ways_to_win{ static_cast<int>(x1 - x2) };

	std::cout << "Value x1: " << x1 << "; Value x2: " << x2 << "; Time: " << time << "; Distance: " << distance << "; Ways to win: " << ways_to_win << "\n";

	std::cout << "\nDay 6 2023 Part 2: " << ways_to_win << "\n\n";
}
