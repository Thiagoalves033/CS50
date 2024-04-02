#include <cs50.h>
#include <stdio.h>
int main(void)
{
    int H;
    do
    {
        H = get_int("Height: ");
    }
    while (H < 1 || H > 8);
    for (int n = 0; n < H; n++)
    {
        for (int w = H - 1; w > n; w--)
        {
            printf(" ");
        }
        for (int z = -1; z < n; z++)
        {
            printf("#");
        }
        for (int y = 0; y < 2; y++)
        {
            printf(" ");
        }
        for (int k = -1; k < n; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}