#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start;
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);

    // TODO: Prompt for end size
    int end;
    do
    {
        end = get_int("End size: ");
    }
    while (end <= start);

    // TODO: Calculate number of years until we reach threshold
    // Populational Growth = start/3 - start/4
    // The growth changes every year
    int i;

    for (i = 0; start < end; i++)
    {
        int growth = start / 3 - start / 4;
        start = start + growth;
    }

    // TODO: Print number of years
    printf("Years: %i\n", i);
}