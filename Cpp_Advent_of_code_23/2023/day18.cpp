#include "day18.h"

void Day18_2023::Part1()
{
	this->input_vector = get_input("2023/Inputs/Day18.txt");
	std::vector<Point> points{};
	std::string str{};
	char direction{};
	int steps{};
	std::pair<int, int> curr_position{ 0, 0 };
	long long border_points{ 0 };

	// Don't need to add starting point because 
	//points.emplace_back(100, 100, str);

	for(const auto& line : input_vector)
	{
		std::istringstream string_stream{ line };
		string_stream >> str;
		direction = str[0];
		string_stream >> str;
		steps = std::stoi(str);
		string_stream >> str;
		str = str.substr(2, 6);

		// Add start
		//points.emplace_back(curr_position.first, curr_position.second, str);

		switch(direction)
		{
		case 'U':
			curr_position.second += steps;
			break;
		case 'R':
			curr_position.first += steps;
			break;
		case 'L':
			curr_position.first -= steps;
			break;
		case 'D':
			curr_position.second -= steps;
			break;
		}

		border_points += steps;

		// Add end
		points.emplace_back(curr_position.first, curr_position.second, str);
	}

	long long area{ calculate_area(points, border_points) };

	std::cout << "Day 18 Part 1 2023: " << area << "\n";
}

void Day18_2023::Part2()
{
	this->input_vector = get_input("2023/Inputs/Day18.txt");
	std::vector<Point> points{};
	std::string str{};
	char direction{};
	long long steps{};
	std::pair<int, int> curr_position{ 0, 0 };
	long long border_points{ 0 };

	// Don't need to add starting point because 
	//points.emplace_back(100, 100, str);

	for (const auto& line : input_vector)
	{
		std::istringstream istring_stream{ line };
		istring_stream >> str >> str >> str;
		str = str.substr(2, 6);
		direction = str[5];
		str = str.substr(0, 5);
		std::stringstream other_stream;
		other_stream << std::hex << str;
		other_stream >> steps;

		// Add start
		//points.emplace_back(curr_position.first, curr_position.second, str);

		switch (direction)
		{
		case '3':
			curr_position.second += steps;
			break;
		case '0':
			curr_position.first += steps;
			break;
		case '2':
			curr_position.first -= steps;
			break;
		case '1':
			curr_position.second -= steps;
			break;
		}

		border_points += steps;

		// Add end
		points.emplace_back(curr_position.first, curr_position.second, str);
	}

	long long area{ calculate_area(points, border_points) };

	std::cout << "Day 18 Part 2 2023: " << area << "\n";
}

long long Day18_2023::calculate_area(std::vector<Point>& points, long long& border_points)
{
	if (points.size() < 3)
	{
		return 0;
	}

	long long area{};

	// First Shoelace
	for (int i = 0; i < points.size(); i++)
	{
		auto& point1 = points[i];
		auto& point2 = points[(i + 1) % points.size()];
		area += point1.x * point2.y;
		area -= point1.y * point2.x;
	}
	area = std::abs(area) / 2;

	// Then Pick's Theorem kinda
	area = area - border_points / 2 + 1 + border_points; 

	return area;
}