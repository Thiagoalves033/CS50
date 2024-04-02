# TODO
from cs50 import get_int

# Proper usage
while True:
    height = get_int("Height: ")
    if height <= 8 and height > 0:
        break

# Printing the pyramid
for i in range(height):
    print(" " * (height - 1 - i), end="")
    print("#" * (i + 1))
