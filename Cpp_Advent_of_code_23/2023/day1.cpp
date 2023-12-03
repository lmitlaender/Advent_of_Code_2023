#include "day1.h"

void Day1_2023::Part1(){
	input_vector = get_input("C:/Advent_of_Code_2023/Cpp_Advent_of_code_23/2023/Inputs/Day1.txt");
	const std::regex regex_pattern{ "[0-9]" };

	int total{ 0 };

	for (const auto& line : input_vector) {
		std::smatch first_match{};
		std::match_results<std::string::const_reverse_iterator> last_match{};

		std::regex_search(line, first_match, regex_pattern);
		std::regex_search(line.crbegin(), line.crend(), last_match, regex_pattern);
		int calibration_value{ std::stoi(first_match.str() + last_match.str())};

		total += calibration_value;
	}

	std::cout << "Day 1 Part 1: " << total << "\n";
}

void Day1_2023::Part2() {
	input_vector = get_input("2023/Inputs/Day1.txt");
	const std::regex regex_pattern{ "[0-9]|one|two|three|four|five|six|seven|eight|nine" };

	int total{ 0 };

	for (const auto& line : input_vector) {
		std::smatch first_match{};
		std::match_results<std::string_view::iterator> last_match{};

		std::regex_search(line, first_match, regex_pattern);

		std::string last{};
		bool found_last{ false };
		int i{ 1 };
		while (!found_last) {
			std::string_view line_view{ line };
			line_view.remove_prefix(line.size() - i);
			found_last = std::regex_search(line_view.begin(), line_view.end(), last_match, regex_pattern);
			if (found_last) {
				last = *last_match.begin();
			}
			i++;
		}

		int calibration_value{ std::stoi(this->map_to_number(*first_match.begin()).append(this->map_to_number(last))) };
		total += calibration_value;
	}

	std::cout << "Day 1 Part 2: " << total << "\n";
}

std::string Day1_2023::map_to_number(const std::string& number_as_string) {
	if (isdigit(number_as_string[0])) {
		return number_as_string;
	}
	else {
		return string_to_number_string[number_as_string];
	}
}