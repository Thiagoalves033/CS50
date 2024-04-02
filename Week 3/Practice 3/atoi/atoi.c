#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    int n = strlen(input);

    // Base case
    if (n == 1)
    {
        return input[0] - '0';
    }
    // Recursive case
    else
    {
        int last = input[n - 1];
        int last_c = last - '0';
        input[n - 1] = '\0';
        return last_c + 10 * convert(input);
    }
}

