#include <stdbool.h>
#include <math.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Getting the average of red, green and blue
            float gray = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;

            // Converting to Grayscale
            image[i][j].rgbtRed = round(gray);
            image[i][j].rgbtGreen = round(gray);
            image[i][j].rgbtBlue = round(gray);
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Converting to Sepia
            float SepiaRed = 0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue;
            float SepiaGreen = 0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue;
            float SepiaBlue = 0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue;

            // Making sure none of the new values are above 255
            if (SepiaRed > 255)
            {
                SepiaRed = 255;
            }

            if (SepiaGreen > 255)
            {
                SepiaGreen = 255;
            }

            if (SepiaBlue > 255)
            {
                SepiaBlue = 255;
            }

            image[i][j].rgbtRed = round(SepiaRed);
            image[i][j].rgbtGreen = round(SepiaGreen);
            image[i][j].rgbtBlue = round(SepiaBlue);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // Swap the pixels
        // 'width / 2' so that the picture doesn't re-swap and remains the same
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the image, so that the values are always applied over the original picture
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Applying Box Blur
    for (int i = 0; i < height; i++)
    {
        float BlurRed;
        float BlurGreen;
        float BlurBlue;

        for (int j = 0; j < width; j++)
        {
            int x;
            int y;

            // Corner - Average of 4 values
            bool corner = false;

            if (i == 0 && j == 0) // Top-Left
            {
                corner = true;
                x = 1;
                y = 1;
            }
            else if (i == 0 && j == width - 1) // Top-Right
            {
                corner = true;
                x = 1;
                y = -1;
            }
            else if (i == height - 1 && j == 0) // Bottom-Left
            {
                corner = true;
                x = -1;
                y = 1;
            }
            else if (i == height - 1 && j == width - 1) // Bottom-Right
            {
                corner = true;
                x = -1;
                y = -1;
            }

            if (corner == true)
            {
                BlurRed = (copy[i][j].rgbtRed + copy[i + x][j].rgbtRed + copy[i][j + y].rgbtRed + copy[i + x][j + y].rgbtRed) / 4.0;
                BlurGreen = (copy[i][j].rgbtGreen + copy[i + x][j].rgbtGreen + copy[i][j + y].rgbtGreen + copy[i + x][j + y].rgbtGreen) / 4.0;
                BlurBlue = (copy[i][j].rgbtBlue + copy[i + x][j].rgbtBlue + copy[i][j + y].rgbtBlue + copy[i + x][j + y].rgbtBlue) / 4.0;
            }

            // Edges - Average of 6 values
            bool edges = false;

            if ((i == 0 || j == 0) && corner == false)
            {
                edges = true;
                x = 1;
                y = 1;
            }
            else if ((i == height - 1 || j == width - 1) && corner == false)
            {
                edges = true;
                x = -1;
                y = -1;
            }

            if ((i == 0 || i == height - 1) && edges == true)
            {
                BlurRed = (copy[i][j].rgbtRed + copy[i + x][j].rgbtRed + copy[i][j + y].rgbtRed + copy[i][j - y].rgbtRed + copy[i + x][j +
                           y].rgbtRed + copy[i + x][j - y].rgbtRed) / 6.0;
                BlurGreen = (copy[i][j].rgbtGreen + copy[i + x][j].rgbtGreen + copy[i][j + y].rgbtGreen + copy[i][j - y].rgbtGreen + copy[i + x][j +
                             y].rgbtGreen + copy[i + x][j - y].rgbtGreen) / 6.0;
                BlurBlue = (copy[i][j].rgbtBlue + copy[i + x][j].rgbtBlue + copy[i][j + y].rgbtBlue + copy[i][j - y].rgbtBlue + copy[i + x][j +
                            y].rgbtBlue + copy[i + x][j - y].rgbtBlue) / 6.0;
            }
            else if ((j == 0 || j == width - 1) && edges == true)
            {
                BlurRed = (copy[i][j].rgbtRed + copy[i + x][j].rgbtRed + copy[i - x][j].rgbtRed + copy[i][j + y].rgbtRed + copy[i + x][j +
                           y].rgbtRed + copy[i - x][j + y].rgbtRed) / 6.0;
                BlurGreen = (copy[i][j].rgbtGreen + copy[i + x][j].rgbtGreen + copy[i - x][j].rgbtGreen + copy[i][j + y].rgbtGreen + copy[i + x][j +
                             y].rgbtGreen + copy[i - x][j + y].rgbtGreen) / 6.0;
                BlurBlue = (copy[i][j].rgbtBlue + copy[i + x][j].rgbtBlue + copy[i - x][j].rgbtBlue + copy[i][j + y].rgbtBlue + copy[i + x][j +
                            y].rgbtBlue + copy[i - x][j + y].rgbtBlue) / 6.0;
            }

            // No special cases - Average of 9 values
            if (corner == false && edges == false)
            {
                BlurRed = (copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed +
                           copy[i - 1][j - 1].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 9.0;
                BlurGreen = (copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j +
                             1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j +
                                     1].rgbtGreen) / 9.0;
                BlurBlue = (copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j +
                            1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j +
                                    1].rgbtBlue) / 9.0;
            }

            image[i][j].rgbtRed = round(BlurRed);
            image[i][j].rgbtGreen = round(BlurGreen);
            image[i][j].rgbtBlue = round(BlurBlue);
        }
    }
}