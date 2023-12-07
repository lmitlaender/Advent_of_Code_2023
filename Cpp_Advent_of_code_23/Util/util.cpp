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
}

void download_input(int year, int day) {
	httplib::Client client("https://adventofcode.com");

	auto res = client.Get(std::format("/{}/day/{}/input", year, day));


	if (res && res->status == 200) {
		// Save the downloaded content to a file
		std::ofstream file(std::format("{}/Inputs/Day{}.txt", year, day), std::ios::binary);
		file.write(res->body.c_str(), res->body.size());
		file.close();

		std::cout << "File downloaded successfully.\n";
	}
	else {
		std::cerr << "Error downloading file. Status code: " << (res ? res->status : -1) << std::endl;
	}
}