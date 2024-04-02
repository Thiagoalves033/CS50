# TODO
from sys import exit


def main():
    # Prompt user for input
    str_number = input("Number: ")
    lenght = len(str_number)
    if lenght in [13, 15, 16]:
        number = int(str_number)
    else:
        print("INVALID")
        exit(1)

    # First digit and the two first digits
    f = int(str_number[0])
    s = int(str_number[0] + str_number[1])

    # Luhn's Algorithm
    if luhn(number) == False:
        print("INVALID")
        exit(1)

    # Checking the company
    if (lenght == 15) and (s in [34, 37]):
        print("AMEX")
    elif (lenght == 16) and (s in [51, 52, 53, 54, 55]):
        print("MASTERCARD")
    elif (lenght in [13, 16]) and (f == 4):
        print("VISA")
    else:
        print("INVALID")


def luhn(number):
    copy = number
    other = 0
    rest = 0

    while True:
        # Non-other digits
        rest += copy % 10
        copy //= 10

        # Other digits
        tmp = (copy % 10) * 2
        if tmp >= 10:
            tmp = (tmp % 10) + (tmp // 10)
        other += tmp
        copy //= 10

        # End loop
        if copy <= 0:
            break

    if ((other + rest) % 10) == 0:
        return True
    else:
        return False


main()
