#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "DayFactory.h"
#include "../2023/day1.h"
#include "../2023/day2.h"
#include "../2023/day3.h"
#include "../2023/day4.h"
#include "../2023/day5.h"
#include "../2023/day6.h"
#include "../2023/day7.h"
#include "IDay.h"

std::vector<std::string> get_input(std::string input_path);

void register_days(DayFactory& day_factory);