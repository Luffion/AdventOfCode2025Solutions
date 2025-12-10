from pulp import LpProblem, LpVariable, LpMinimize, lpSum, LpInteger, PULP_CBC_CMD
import re

def readfile(filename):
    buttons_array = []
    joltage_array = []

    with open(filename, "r") as f:
        for line in f:
            line = line.strip()
            if not line:
                continue

            button_groups = re.findall(r'\((.*?)\)', line)
            buttons = [list(map(int, group.split(','))) for group in button_groups]

            joltage_match = re.search(r'\{(.*?)\}', line)
            joltage = list(map(int, joltage_match.group(1).split(','))) if joltage_match else []

            buttons_array.append(buttons)
            joltage_array.append(joltage)

    return buttons_array, joltage_array

def solveILP(buttons_array, joltage_array):
    total_presses = 0

    for buttons, target in zip(buttons_array, joltage_array):
        n_buttons = len(buttons)
        n_counters = len(target)

        prob = LpProblem("MinimiseButtonPresses", LpMinimize)

        x = [LpVariable(f"x{i}", lowBound=0, cat=LpInteger) for i in range(n_buttons)]

        prob += lpSum(x)

        for j in range(n_counters):
            prob += lpSum(x[i] for i in range(n_buttons) if j in buttons[i]) == target[j]

        prob.solve(PULP_CBC_CMD(msg=False))

        machine_presses = sum(var.varValue for var in x)
        total_presses += int(machine_presses)

    return total_presses

buttons_array, joltage_array = readfile("data.txt")
result = solveILP(buttons_array, joltage_array)
print("Part 2 Solution: ", result)
