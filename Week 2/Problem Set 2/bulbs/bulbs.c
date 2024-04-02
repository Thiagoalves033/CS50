#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    int reverse[BITS_IN_BYTE];

    // Getting user input
    string message = get_string("Message: ");

    // A character is just a number. Print the numbers
    for (int i = 0, n = strlen(message); i < n; i++)
    {
        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            reverse[j] = message[i] % 2;
            message[i] /= 2;
        }

        for (int k = BITS_IN_BYTE - 1; k >= 0 ; k--)
        {
            print_bulb(reverse[k]);
        }

        printf("\n");

    }

}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
