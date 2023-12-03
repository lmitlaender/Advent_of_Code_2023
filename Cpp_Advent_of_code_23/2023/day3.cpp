#include "day3.h"

void Day3_2023::Part1() {
	this->input_vector = get_input("2023/Inputs/Day3.txt");

	const std::regex pattern("\\d+");
	int line_no{ 0 };
	int total{ 0 };

	for (const auto& line : input_vector) {
		std::sregex_iterator it{ line.begin(), line.end(), pattern };
		std::sregex_iterator end;

		while (it != end) {
			std::smatch match = *it;
			if (this->check_match(line_no, match.position(), match.length())) {
				total += std::stoi(match.str());
			}
			++it;
		}
		line_no++;
	}
	
	std::cout << "Day 3 2023 Part 1: " << total << "\n";
}

void Day3_2023::Part2() {
	this->input_vector = get_input("2023/Inputs/Day3.txt");

	const std::regex pattern("\\d+|\\*");
	int line_no{ 0 };
	int uid{ 1 };
	std::vector<std::string> values_vec{};
	std::vector<std::tuple<int, int>> star_vec{};
	int total{ 0 };

	for (const auto& line : input_vector) {
		std::sregex_iterator it{ line.begin(), line.end(), pattern };
		std::sregex_iterator end;

		while (it != end) {
			std::smatch match = *it;
			if (*match.begin() == '*') {
				star_vec.push_back(std::tuple{ line_no, match.position() });
			}
			else {
				for (int i = match.position(); i < match.position() + match.length(); i++) {
					digit_at[std::tuple{ line_no, i }] = uid;
					if (i == match.position() + match.length() - 1) {
						values_vec.push_back(match.str());
						uid++;
					}
				}
			}
			++it;
		}
		line_no++;
	}

	std::vector<std::tuple<int, int>> offsets{ {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };

	for (auto coordinates : star_vec) {
		std::set<int> values_adjacent{};
		for (auto offset : offsets) {
			std::tuple<int, int> check_tuple{ std::get<0>(coordinates) + std::get<0>(offset), std::get<1>(coordinates) + std::get<1>(offset) };
			if (digit_at.contains(check_tuple))
				values_adjacent.insert(digit_at[check_tuple]);
		}

		if (values_adjacent.size() == 2) {
			std::vector<int> entries{ values_adjacent.begin(), values_adjacent.end() };
			total += std::stoi(values_vec[entries[0] - 1]) * std::stoi(values_vec[entries[1] - 1]);
		}
	}

	std::cout << "Day 3 2023 Part 2: " << total << "\n";
}

bool Day3_2023::check_match(const int& line_no,  const int match_pos, const int match_length) {
	const int match_end{ match_pos + match_length - 1 };

	if (match_pos != 0) {
		if (is_symbol(input_vector[line_no][match_pos - 1]))
			return true;
	}
	if (match_pos != 0 && line_no != 0) {
		if (is_symbol(input_vector[line_no - 1][match_pos - 1]))
			return true;
	}
	if (match_pos != 0 && line_no != input_vector.size() - 1) {
		if (is_symbol(input_vector[line_no + 1][match_pos - 1]))
			return true;
	}

	if (match_end != input_vector[line_no].length() - 1) {
		if (is_symbol(input_vector[line_no][match_end + 1]))
			return true;
	}
	if (match_end != input_vector[line_no].length() - 1 && line_no != 0) {
		if (is_symbol(input_vector[line_no - 1][match_end + 1]))
			return true;
	}
	if (match_end != input_vector[line_no].length() - 1 && line_no != input_vector.size() - 1) {
		if (is_symbol(input_vector[line_no + 1][match_end + 1]))
			return true;
	}

	if (line_no != 0) {
		for (int i = match_pos; i < match_pos + match_length; i++) {
			if (is_symbol(input_vector[line_no - 1][i]))
				return true;
		}
	}
	if (line_no != input_vector.size() - 1) {
		for (int i = match_pos; i < match_pos + match_length; i++) {
			if (is_symbol(input_vector[line_no + 1][i]))
				return true;
		}
	}
	return false;
}

bool Day3_2023::is_symbol(const char& c) {

	if ('.' == c) {
		return false;
	}
	if (std::isalpha(c)) {
		return false;
	} 
	if (std::isdigit(c)) {
		return false;
	}

	return true;
}