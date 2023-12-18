cmake_minimum_required(VERSION 3.20.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(AoC VERSION 0.1.0 LANGUAGES C CXX)



################################################################################
# Source, target, and executable
################################################################################
set(2023_source
    2023/day1.cpp
    2023/day2.cpp
    2023/day3.cpp
    2023/day4.cpp
    2023/day5.cpp
    2023/day6.cpp
    2023/day7.cpp
    2023/day8.cpp
    2023/day9.cpp
        2023/day10.cpp)
source_group("Source Files\\2023" FILES ${2023_source})

set(Util_source
    Util/DayFactory.cpp
    Util/util.cpp)
source_group("Source Files\\Util" FILES ${Util_source})

set(ALL_SOURCE
    ${2023_source}
    ${Util_source} "2023/day11.cpp" "2023/day12.cpp")

add_executable(AoC main.cpp ${ALL_SOURCE} "2023/day13.cpp" "2023/day13.h" "2023/day14.cpp" "2023/day14.h" "2023/day16.cpp" "2023/day17.cpp" "2023/day18.cpp")
set_target_properties(AoC PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(AoC PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(AoC PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(AoC PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces ${CMAKE_CURRENT_SOURCE_DIR}/2023 ${CMAKE_CURRENT_SOURCE_DIR}/Util)