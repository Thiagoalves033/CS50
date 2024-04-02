#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Program takes only a single argument
    if (argc != 2)
    {
        printf("Usage: ./recover <IMAGE>\n");
        return 1;
    }

    // Open the forensic image
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Reading the file
    char filename[8];
    FILE *output = NULL;
    BYTE buffer[512];
    int i = 0;

    while (fread(&buffer, 512, 1, input) == 1)
    {
        // Check if it's the start of a JPEG file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If it's the very first JPEG, start writing
            if (i == 0)
            {
                sprintf(filename, "%03i.jpg", i);
                output = fopen(filename, "w");
                fwrite(&buffer, 512, 1, output);
                i++;
            }

            // If not, close the previous file and open a new one
            else
            {
                fclose(output);
                sprintf(filename, "%03i.jpg", i);
                output = fopen(filename, "w");
                fwrite(&buffer, 512, 1, output);
                i++;
            }
        }

        // Keep writing
        else
        {
            if (output != NULL)
            {
                fwrite(&buffer, 512, 1, output);
            }
        }
    }

    // Close the files
    fclose(input);
    if (output != NULL)
    {
        fclose(output);
    }
}