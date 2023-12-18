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
#include "../2023/day8.h"
#include "../2023/day9.h"
#include "../2023/day10.h"
#include "../2023/day11.h"
#include "../2023/day12.h"
#include "../2023/day13.h"
#include "../2023/day14.h"
#include "../2023/day16.h"
#include "../2023/day17.h"
#include "../2023/day18.h"
#include "IDay.h"


std::vector<std::string> get_input(std::string input_path);

void register_days(DayFactory& day_factory);