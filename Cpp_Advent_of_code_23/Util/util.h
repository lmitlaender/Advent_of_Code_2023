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
#include "IDay.h"

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
#ifdef _WIN32
#include <Windows.h>
#endif

std::vector<std::string> get_input(std::string input_path);

void register_days(DayFactory& day_factory);

void download_input(int year, int day);