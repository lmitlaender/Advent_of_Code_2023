import os
from typing import List

input_file = "input.txt"
file_path = os.path.join(os.path.dirname(__file__), input_file)

limits = {"red": 12, "green": 13, "blue": 14}

def split_set(text: str) -> List[str]: 
    sets = text.split(";")
    return sets

def check_for_set(set: str) -> bool:
    cubes_by_color = set.split(",")
    for cubes in cubes_by_color:
        if not check_for_color(cubes):
            return False
    return True
    
def check_for_color(color_string: str) -> bool:
    color_string = color_string.strip()
    count_and_color = color_string.split(" ")
    if int(count_and_color[0]) > limits[count_and_color[1]]:
        return False
    return True

def obtain_game_num_and_sets_text(line: str) -> (int, str):
    colon_pos = line.find(":")
    game_text = line[:colon_pos]
    set_text = line[colon_pos + 1:]
    game = int(game_text[5:])
    return game, set_text

def get_min_power_per_game(sets: List[str]) -> int:
    min = {"red": 0, "green": 0, "blue": 0}
    for set in sets:
        num_by_colours = set.split(",")
        for color in num_by_colours:
            color = color.strip()
            count_and_color = color.split(" ")
            if min[count_and_color[1]] < int(count_and_color[0]):
                min[count_and_color[1]] = int(count_and_color[0])

    return get_power(**min)
        
def get_power(red, green, blue):
    return red * green * blue
            
def part1() -> int:
    total = 0
    
    with open(file_path, "r") as file:
        lines = file.readlines()
        for line in lines:
            game, set_text = obtain_game_num_and_sets_text(line=line)
            sets = split_set(text=set_text)
            possible = True
            for set in sets:
                if not check_for_set(set=set):
                    possible = False
                    break
            if possible:
                total += game
    
    return total

def part2() -> int:
    total = 0
    
    with open(file_path, "r") as file:
        lines = file.readlines()
        for line in lines:
            game, set_text = obtain_game_num_and_sets_text(line=line)
            sets = split_set(text=set_text)
            power = get_min_power_per_game(sets=sets)
            total += power
    
    return total
    
                
print("Part1: ", part1())
print("Part 2: ", part2())