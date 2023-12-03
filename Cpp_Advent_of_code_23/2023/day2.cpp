#include "day2.h"

void Day2_2023::Part1() {
	// Using stringstream for this solution to test out how it works
	this->input_vector = get_input("2023/Inputs/Day2.txt");

	int total{};

	for (const auto& line : input_vector) {
		std::istringstream stream{ line };
		std::string str;
		int game;
		stream >> str >> str;
		str.pop_back();
		game = std::stoi(str);

		bool valid{ true };
		while (!stream.eof()) {
			stream >> str;
			int number = std::stoi(str);
			stream >> str;
			if (*(str.end() - 1) == ',' || *(str.end() - 1) == ';') {
				str.pop_back();
			}
			if (limits[str] < number) {
				valid = false;
				break;
			}
		}
		if (valid) {
			total += game;
		}
	}

	std::cout << "Day 2 Part 1: " << total << "\n";
}

void Day2_2023::Part2() {
	// And using find and the like for this one to test that
	this->input_vector = get_input("2023/Inputs/Day2.txt");
	
	int total{};

	for (auto& line : input_vector) {
		std::unordered_map<std::string, int> min{ {"red", 0}, {"blue", 0}, {"green", 0} };

		auto colon_pos = line.find_first_of(':');
		//int game{ std::stoi(line.substr(std::size_t(5), colon_pos - std::size_t(5))) };

		line.erase(0, colon_pos + 2); // 2 for : and space

		size_t pos{};
		std::vector<std::string> sets{};

		while ((pos = line.find(";")) != std::string::npos) {
			sets.push_back(line.substr(0, pos));
			line.erase(0, pos + 2);
		}
		sets.push_back(line);

		std::vector<std::string> color_numbers{};
		for (auto set : sets) {
			while ((pos = set.find(",")) != std::string::npos) {
				color_numbers.push_back(set.substr(0, pos));
				set.erase(0, pos + 2);
			}
			color_numbers.push_back(set);
		}

		for (auto color : color_numbers) {
			pos = color.find_last_of(" ");
			int num = std::stoi(color.substr(0, pos));
			std::string color_name = color.substr(pos + 1, color.size());
			if (min[color_name] < num) {
				min[color_name] = num;
			}
		}

		total += min["red"] * min["blue"] * min["green"];
	}

	std::cout << "Day 2 Part 2: " << total << "\n";
}