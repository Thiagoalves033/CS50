# TODO
from cs50 import get_float

# Getting user input
while True:
    change = get_float("Change owed: ")
    if change > 0:
        break

# Calculating the minimum number of coins
min = 0

# Quarters
while True:
    if change >= 0.25:
        change = round(change - 0.25, 2)
        min += 1
    else:
        break

# Dimes
while True:
    if change >= 0.10:
        change = round(change - 0.10, 2)
        min += 1
    else:
        break

# Nickels
while True:
    if change >= 0.05:
        change = round(change - 0.05, 2)
        min += 1
    else:
        break

# Pennies
while True:
    if change >= 0.01:
        change = round(change - 0.01, 2)
        min += 1
    else:
        break

# Printing the value
print(f"{min}")
