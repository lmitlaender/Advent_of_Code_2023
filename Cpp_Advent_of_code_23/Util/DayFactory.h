#pragma once
#include "IDay.h"
#include <functional>
#include <map>
#include <tuple>


class DayFactory {
public:
	IDay* create(int year, int day);
	void register_solution(int year, int day, std::function<IDay* ()> func);

private:
	std::map<std::tuple<int, int>, std::function<IDay* ()>> registry;
};