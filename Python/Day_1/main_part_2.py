import re
import os

input_file = "input.txt"
file_path = os.path.join(os.path.dirname(__file__), input_file)

regex_pattern = r"(?=([0-9]|one|two|three|four|five|six|seven|eight|nine))"

digit_list = list(range(1, 10))
digit_list = [str(x) for x in digit_list]
written_list = ["one", "two", "three" , "four", "five", "six", "seven", "eight", "nine"]
dict = dict(zip(written_list, digit_list))

def number_replacer(text):
    if text in dict.keys():
        return dict[text]
    return text

total = 0

with  open(file_path, mode="r") as file:
    lines = file.readlines()
    
    for line in lines:
        matches = re.findall(pattern=regex_pattern, string=line)
        matches = ["".join(x) for x in matches]
        matches = [x for x in matches if x != ""]
        calibration_value = number_replacer(matches[0]) + number_replacer(matches[-1])
        total += int(calibration_value)
        
print(total)