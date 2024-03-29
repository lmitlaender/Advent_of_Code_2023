#include "util.h"

std::vector<std::string> get_input(std::string input_path) {
	std::ifstream input_file{ input_path };
	std::string line{};
	std::vector<std::string> lines_vector;


	if (input_file.is_open()) {
		while (std::getline(input_file, line)) {
			lines_vector.push_back(line); // Add line at end of vector
		}
		input_file.close();
	}
	else {
		std::cerr << "Failed to open file at " << input_path << "!\n";
	}

	return lines_vector;
}

void register_days(DayFactory& day_factory) {
	day_factory.register_solution(2023, 1, []() { return new Day1_2023(); });
	day_factory.register_solution(2023, 2, []() { return new Day2_2023(); });
	day_factory.register_solution(2023, 3, []() { return new Day3_2023(); });
	day_factory.register_solution(2023, 4, []() { return new Day4_2023(); });
	day_factory.register_solution(2023, 5, []() { return new Day5_2023(); });
	day_factory.register_solution(2023, 6, []() { return new Day6_2023(); });
	day_factory.register_solution(2023, 7, []() { return new Day7_2023(); });
	day_factory.register_solution(2023, 8, []() { return new Day8_2023(); });
	day_factory.register_solution(2023, 9, []() { return new Day9_2023(); });
	day_factory.register_solution(2023, 10, []() { return new Day10_2023(); });
	day_factory.register_solution(2023, 11, []() { return new Day11_2023(); });
	day_factory.register_solution(2023, 12, []() { return new Day12_2023(); });
	day_factory.register_solution(2023, 13, []() { return new Day13_2023(); });
	day_factory.register_solution(2023, 14, []() { return new Day14_2023(); });
	day_factory.register_solution(2023, 16, []() { return new Day16_2023(); });
	day_factory.register_solution(2023, 17, []() { return new Day17_2023(); });
	day_factory.register_solution(2023, 18, []() { return new Day18_2023(); });
}