#include <iostream>
#include "IDay.h"
#include "DayFactory.h"
#include "util.h"
#include <chrono>

int main()
{
    std::string year{};
    std::string day{};

    std::cout << "Enter a year: ";
    std::cin >> year;
    std::cout << "Enter a day: ";
    std::cin >> day;
    std::cout << "\n\n";

    auto day_factory = DayFactory();
    register_days(day_factory);

    auto instance = day_factory.create(std::stoi(year), std::stoi(day));

    auto start_part_1 = std::chrono::high_resolution_clock::now();
    instance->Part1();
    auto start_part_2 = std::chrono::high_resolution_clock::now();
    instance->Part2();
    auto end_time = std::chrono::high_resolution_clock::now();

    std::cout << "Part 1 Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(start_part_2 - start_part_1) << "\n";
    std::cout << "Part 2 Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_part_2) << "\n";

    system("pause");

    return 0;
}

