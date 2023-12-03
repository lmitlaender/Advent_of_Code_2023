#include "DayFactory.h"

void DayFactory::register_solution(int year, int day, std::function<IDay* ()> func) {
	std::tuple year_day_tuple{ year, day };

	this->registry[year_day_tuple] = func;
}

IDay* DayFactory::create(int year, int day) {
	std::tuple year_day_tuple{ year, day };

	auto func = this->registry[year_day_tuple];
	return func();
}