#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "DayFactory.h"
#include "../2023/day1.h"
#include "IDay.h"

std::vector<std::string> get_input(std::string input_path);

void register_days(DayFactory& day_factory);