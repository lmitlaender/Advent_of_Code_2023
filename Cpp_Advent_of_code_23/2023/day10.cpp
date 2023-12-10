#include "day10.h"

void Day10_2023::Part1()
{
    this->input_vector = get_input("2023/Inputs/Day10.txt");

    std::vector<std::pair<int, int>> prevs{};
    auto points {this->get_starting_points(input_vector, prevs)};
    std::vector<int> distance{};
    for (auto& point : points) {
        distance.emplace_back(1);
    }

    // We know that there are always two points since the task says there's always two connections. since it is a loop the furthest point is when both of the points meet.
    while (points[0] != points[1])
    {
        for (int i = 0; i < points.size(); i++) {
            this->get_next(input_vector[points[i].second][points[i].first], points[i], prevs[i]);
            distance[i]++;
        }
    }

    std::cout << "Day 10 2023 Part 1: " << distance[0] << " highest_distance\n";
}

void Day10_2023::Part2()
{
    this->input_vector = get_input("2023/Inputs/Day10.txt");

    std::vector<std::pair<int, int>> prevs{};
    auto points{ this->get_starting_points(input_vector, prevs) };
    std::vector<int> distance{};
    std::vector<std::pair<int, int>> boundary_nodes{};
    boundary_nodes.push_back(prevs[0]);
    for (auto& point : points) {
        distance.emplace_back(1);
    }

    auto starting_point = prevs[0];

    // Get the boundary points in order for shoelace theorem to calculate area.
	while (points[0] != starting_point)
    {
        boundary_nodes.push_back(points[0]);
        this->get_next(input_vector[points[0].second][points[0].first], points[0], prevs[0]);
        distance[0]++;
    }

	// calculation uses Picks Theorem and Shoelace Formula to calculate the area inside of the boundary.
    // Other Idea I had was to either find all squares, or expand each point by two and add a boundary around, and then look for all reachable non boundary points.
    // But I definitely cheated a bit looking up the Math solution, but that's probably the best solution there is(?) I'd think.
    std::cout << "Day 10 2023 Part 2: " << calculate_area(boundary_nodes) << "\n";
}

void Day10_2023::get_next(const char& current, std::pair<int, int>& curr,  std::pair<int, int>& prev) {
    const std::pair new_prev { curr };

    switch (current) {
        case '|': prev.second < curr.second ? curr.second++ : curr.second--; break;
        case '-': prev.first < curr.first ? curr.first++ : curr.first--; break;
        case 'L': prev.second != curr.second ? curr.first++ : curr.second--; break;
        case 'J': prev.second != curr.second ? curr.first-- : curr.second--; break;
        case '7': prev.second != curr.second ? curr.first-- : curr.second++; break;
        case 'F': prev.second != curr.second ? curr.first++ : curr.second++; break;
    }

    prev = new_prev;
}

std::vector<std::pair<int, int>> Day10_2023::get_starting_points(const std::vector<std::string>& input, std::vector<std::pair<int, int>>& prevs) {
    std::vector<std::pair<int, int>> starting_points{};
    size_t pos{};

    for (int i = 0; i < input.size(); i++) {
        pos = input[i].find('S');
        if (pos != std::string::npos) {
            if (i != 0 && (input[i - 1][pos] == '|' || input[i - 1][pos] == 'F' || input[i - 1][pos] == '7')) {
                starting_points.emplace_back(pos, i - 1);
                prevs.emplace_back(pos, i);
            }
            if (i != input.size() - 1 && (input[i + 1][pos] == '|' || input[i + 1][pos] == 'L' || input[i + 1][pos] == 'J')) {
                starting_points.emplace_back(pos, i + 1);
                prevs.emplace_back(pos, i);
            }
            if (pos != 0 && (input[i][pos - 1] == '-' || input[i][pos - 1] == 'L' || input[i][pos - 1] == 'F')) {
                starting_points.emplace_back(pos - 1, i);
                prevs.emplace_back(pos, i);
            }
            if (i != input[i].size() - 1 && (input[i][pos + 1] == '-' || input[i][pos + 1] == '7' || input[i][pos + 1] == 'J')) {
                starting_points.emplace_back(pos + 1, i);
                prevs.emplace_back(pos, i);
            }
            break;
        }
    }

    return starting_points;
}

int Day10_2023::calculate_area(std::vector<std::pair<int, int>>& ordered_boundary_points)
{
	if (ordered_boundary_points.size() < 3)
	{
        return 0;
	}

    int area{};

    // First Shoelace
    for (int i = 0; i < ordered_boundary_points.size(); i++)
    {
        auto& point1 = ordered_boundary_points[i];
        auto& point2 = ordered_boundary_points[(i + 1) % ordered_boundary_points.size()];
        area += (point1.first * point2.second - point2.first * point1.second);
    }
    area /= 2;
    area = std::abs(area);

    // Then Pick's Theorem kinda, I really need to.. like refresh my math basics I guess.. idk if this really counts as basic though :roll:
    int result = ((area + 1) * 2) - ordered_boundary_points.size();

    return result / 2;
}