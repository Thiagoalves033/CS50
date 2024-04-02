#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open input file.\n");
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER buffer;
    fread(&buffer, 44, 1, input);

    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(buffer) == 1)
    {
        printf("Not a WAV file.\n");
        return 1;
    }

    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open output file.\n");
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&buffer, 44, 1, output);

    // Use get_block_size to calculate size of each block
    // TODO #7
    int block = get_block_size(buffer);

    // Write reversed audio to file
    // TODO #8
    BYTE b_buffer[block];

    int header = ftell(input);
    fseek(input, -block, SEEK_END);

    while (ftell(input) >= header)
    {
        fread(&b_buffer, block, 1, input);
        fwrite(&b_buffer, block, 1, output);
        fseek(input, -block * 2, SEEK_CUR);
    }

    // Closing the files
    fclose(input);
    fclose(output);
}

int check_format(WAVHEADER header)
{
    // Check if bytes 8 to 11 spells 'W''A''V''E'.
    // TODO #4
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int get_block_size(WAVHEADER header)
{
    // Multiply the number of channels by bytes per sample
    // TODO #7
    int size = header.numChannels * header.bitsPerSample / 8;
    return size;
}