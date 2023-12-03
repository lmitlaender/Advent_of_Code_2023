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
}