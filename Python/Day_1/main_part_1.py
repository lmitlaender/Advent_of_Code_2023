import re
import os

regex_pattern = "[0-9]"
input_file = "input.txt"
file_path = os.path.join(os.path.dirname(__file__), input_file)


total = 0

with  open(file_path, mode="r") as file:
    lines = file.readlines()
    
    for line in lines:
        matches = re.findall(pattern=regex_pattern, string=line)
        calibration_value = matches[0] + matches[-1]
        print(calibration_value)
        total += int(calibration_value)
        
print(total)