#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char buffer[7];

    // Create array to store plate numbers
    char *plates[8];

    // Allocate enough space in memory for each element of plates array
    for (int i = 0; i < 8; i++)
    {
        plates[i] = malloc(sizeof(buffer));
        if (plates[i] == NULL)
        {
            return 2;
        }
    }

    // Creating pointer to file
    // 'fopen' allocates memory of size 'sizeof FILE'
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        return 3;
    }

    // Printing out the plates
    for (int idx = 0; fread(buffer, 1, 7, infile) == 7; idx++)
    {
        buffer[6] = '\0';
        strcpy(plates[idx], buffer);
    }

    for (int i = 0; i < 8; i++)
    {
        printf("%s\n", plates[i]);
    }

    // Freeing the used memory
    for (int i = 0; i < 8; i++)
    {
        free(plates[i]);
    }

    // Closing the file
    fclose(infile);

    return 0;
}
