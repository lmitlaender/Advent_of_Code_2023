#pragma once
#include "util.h"
#include "IDay.h"
#include <vector>
#include <string>

class Day18_2023 : public IDay {
public:
    void Part1();
    void Part2();
    std::vector<std::string> input_vector;

private:
    struct Point
    {
        long long x;
        long long y;
        std::string rgb;

        Point(long long x, long long y, std::string& rgb) : x(x), y(y), rgb(rgb){}
    };

    long long calculate_area(std::vector<Point>& points, long long& border_points);
};