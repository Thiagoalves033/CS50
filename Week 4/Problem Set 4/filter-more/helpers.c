#include <stdbool.h>
#include <math.h>
#include <stdio.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Getting the average
            float average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;

            // Converting to Grayscale
            image[i][j].rgbtRed = round(average);
            image[i][j].rgbtGreen = round(average);
            image[i][j].rgbtBlue = round(average);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap the pixels
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        int GxRed = 0;
        int GxGreen = 0;
        int GxBlue = 0;

        int GyRed = 0;
        int GyGreen = 0;
        int GyBlue = 0;

        for (int j = 0; j < width; j++)
        {
            int x;
            int y;
            int z;
            int w;

            // Corners
            bool corner = false;
            if (i == 0 && j == 0) // Top-Left
            {
                corner = true;
                x = 1;
                y = 1;
                z = 2;
                w = 1;
            }
            else if (i == 0 && j == width - 1) // Top-Right
            {
                corner = true;
                x = -1;
                y = 1;
                z = -2;
                w = -1;
            }
            else if (i == height - 1 && j == 0) // Bottom-Left
            {
                corner = true;
                x = 1;
                y = -1;
                z = 2;
                w = 1;
            }
            else if (i == height - 1 && j == width - 1) // Bottom-Right
            {
                corner = true;
                x = -1;
                y = -1;
                z = -2;
                w = -1;
            }

            if (corner == true)
            {
                // Gx
                GxRed = (copy[i][j + x].rgbtRed * z) + (copy[i + y][j + x].rgbtRed * w);
                GxGreen = (copy[i][j + x].rgbtGreen * z) + (copy[i + y][j + x].rgbtGreen * w);
                GxBlue = (copy[i][j + x].rgbtBlue * z) + (copy[i + y][j + x].rgbtBlue * w);

                // Gy
                if ((i == height - 1 && j == 0) || (i == 0 && j == width - 1))
                {
                    GyRed = (copy[i + y][j].rgbtRed * -z) + (copy[i + y][j + x].rgbtRed * -w);
                    GyGreen = (copy[i + y][j].rgbtGreen * -z) + (copy[i + y][j + x].rgbtGreen * -w);
                    GyBlue = (copy[i + y][j].rgbtBlue * -z) + (copy[i + y][j + x].rgbtBlue * -w);
                }
                else
                {
                    GyRed = (copy[i + y][j].rgbtRed * z) + (copy[i + y][j + x].rgbtRed * w);
                    GyGreen = (copy[i + y][j].rgbtGreen * z) + (copy[i + y][j + x].rgbtGreen * w);
                    GyBlue = (copy[i + y][j].rgbtBlue * z) + (copy[i + y][j + x].rgbtBlue * w);
                }
            }

            // Edges
            bool edges = false;

            if ((i == 0 || j == 0) && corner == false)
            {
                edges = true;
                x = 1;
                y = 1;
                z = 1;
                w = 2;
            }
            else if ((i == height - 1 || j == width - 1) && corner == false)
            {
                edges = true;
                x = -1;
                y = -1;
                z = -1;
                w = -2;
            }

            if ((j == 0 || j == width - 1) && edges == true)
            {
                //Gx
                GxRed = (copy[i + y][j + x].rgbtRed * z) + (copy[i][j + x].rgbtRed * w) + (copy[i - y][j + x].rgbtRed * z);
                GxGreen = (copy[i + y][j + x].rgbtGreen * z) + (copy[i][j + x].rgbtGreen * w) + (copy[i - y][j + x].rgbtGreen * z);
                GxBlue = (copy[i + y][j + x].rgbtBlue * z) + (copy[i][j + x].rgbtBlue * w) + (copy[i - y][j + x].rgbtBlue * z);

                //Gy
                GyRed = (copy[i + y][j].rgbtRed * w) + (copy[i - y][j].rgbtRed * -w) + (copy[i + y][j + x].rgbtRed * z) +
                        (copy[i - y][j + x].rgbtRed * -z);
                GyGreen = (copy[i + y][j].rgbtGreen * w) + (copy[i - y][j].rgbtGreen * -w) + (copy[i + y][j + x].rgbtGreen * z) +
                          (copy[i - y][j + x].rgbtGreen * -z);
                GyBlue = (copy[i + y][j].rgbtBlue * w) + (copy[i - y][j].rgbtBlue * -w) + (copy[i + y][j + x].rgbtBlue * z) +
                         (copy[i - y][j + x].rgbtBlue * -z);

            }
            else if ((i == 0 || i == height - 1) && edges == true)
            {
                // Gx
                GxRed = (copy[i][j - x].rgbtRed * -w) + (copy[i][j + x].rgbtRed * w) + (copy[i + y][j + x].rgbtRed * z) +
                        (copy[i + y][j - x].rgbtRed * -z);
                GxGreen = (copy[i][j - x].rgbtGreen * -w) + (copy[i][j + x].rgbtGreen * w) + (copy[i + y][j + x].rgbtGreen * z) +
                          (copy[i + y][j - x].rgbtGreen * -z);
                GxBlue = (copy[i][j - x].rgbtBlue * -w) + (copy[i][j + x].rgbtBlue * w) + (copy[i + y][j + x].rgbtBlue * z) +
                         (copy[i + y][j - x].rgbtBlue * -z);

                //Gy
                GyRed = (copy[i + y][j - x].rgbtRed * z) + (copy[i + y][j].rgbtRed * w) + (copy[i + y][j + x].rgbtRed * z);
                GyGreen = (copy[i + y][j - x].rgbtGreen * z) + (copy[i + y][j].rgbtGreen * w) + (copy[i + y][j + x].rgbtGreen * z);
                GyBlue = (copy[i + y][j - x].rgbtBlue * z) + (copy[i + y][j].rgbtBlue * w) + (copy[i + y][j + x].rgbtBlue * z);
            }
//STOP STOP STOP
            // Middle
            if (corner == false && edges == false)
            {
                // Gx
                GxRed = (copy[i - 1][j - 1].rgbtRed * -1) + (copy[i - 1][j].rgbtRed * 0) + (copy[i - 1][j + 1].rgbtRed * 1) +
                        (copy[i][j - 1].rgbtRed * -2) + (copy[i][j].rgbtRed * 0) + (copy[i][j + 1].rgbtRed * 2) + (copy[i + 1][j - 1].rgbtRed * -1) +
                        (copy[i + 1][j].rgbtRed * 0) + (copy[i + 1][j + 1].rgbtRed * 1);
                GxGreen = (copy[i - 1][j - 1].rgbtGreen * -1) + (copy[i - 1][j].rgbtGreen * 0) + (copy[i - 1][j + 1].rgbtGreen * 1) +
                          (copy[i][j - 1].rgbtGreen * -2) + (copy[i][j].rgbtGreen * 0) + (copy[i][j + 1].rgbtGreen * 2) +
                          (copy[i + 1][j - 1].rgbtGreen * -1) + (copy[i + 1][j].rgbtGreen * 0) + (copy[i + 1][j + 1].rgbtGreen * 1);
                GxBlue = (copy[i - 1][j - 1].rgbtBlue * -1) + (copy[i - 1][j].rgbtBlue * 0) + (copy[i - 1][j + 1].rgbtBlue * 1) +
                         (copy[i][j - 1].rgbtBlue * -2) + (copy[i][j].rgbtBlue * 0) + (copy[i][j + 1].rgbtBlue * 2) +
                         (copy[i + 1][j - 1].rgbtBlue * -1) + (copy[i + 1][j].rgbtBlue * 0) + (copy[i + 1][j + 1].rgbtBlue * 1);

                // Gy
                GyRed = (copy[i - 1][j - 1].rgbtRed * -1) + (copy[i - 1][j].rgbtRed * -2) + (copy[i - 1][j + 1].rgbtRed * -1) +
                        (copy[i][j - 1].rgbtRed * 0) + (copy[i][j].rgbtRed * 0) + (copy[i][j + 1].rgbtRed * 0) + (copy[i + 1][j - 1].rgbtRed * 1) +
                        (copy[i + 1][j].rgbtRed * 2) + (copy[i + 1][j + 1].rgbtRed * 1);
                GyGreen = (copy[i - 1][j - 1].rgbtGreen * -1) + (copy[i - 1][j].rgbtGreen * -2) + (copy[i - 1][j + 1].rgbtGreen * -1) +
                          (copy[i][j - 1].rgbtGreen * 0) + (copy[i][j].rgbtGreen * 0) + (copy[i][j + 1].rgbtGreen * 0) + (copy[i + 1][j - 1].rgbtGreen * 1) +
                          (copy[i + 1][j].rgbtGreen * 2) + (copy[i + 1][j + 1].rgbtGreen * 1);
                GyBlue = (copy[i - 1][j - 1].rgbtBlue * -1) + (copy[i - 1][j].rgbtBlue * -2) + (copy[i - 1][j + 1].rgbtBlue * -1) +
                         (copy[i][j - 1].rgbtBlue * 0) + (copy[i][j].rgbtBlue * 0) + (copy[i][j + 1].rgbtBlue * 0) + (copy[i + 1][j - 1].rgbtBlue * 1) +
                         (copy[i + 1][j].rgbtBlue * 2) + (copy[i + 1][j + 1].rgbtBlue * 1);
            }

            // Sobel Filter
            int SobRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
            int SobGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
            int SobBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));

            // Capping if needed
            if (SobRed > 255)
            {
                SobRed = 255;
            }

            if (SobGreen > 255)
            {
                SobGreen = 255;
            }

            if (SobBlue > 255)
            {
                SobBlue = 255;
            }

            //Applying
            image[i][j].rgbtRed = SobRed;
            image[i][j].rgbtGreen = SobGreen;
            image[i][j].rgbtBlue = SobBlue;
        }
    }
}