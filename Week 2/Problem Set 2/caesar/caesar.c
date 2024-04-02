#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool only_digits(string s);
char rotate(char c, int i);

int main(int argc, string argv[])
{
    // Correct usage
    if (argc != 2)
    {
        printf("Usage: ./caesar <numeric key>\n");
        return 1;
    }
    else if (only_digits(argv[1]) == false)
    {
        printf("Usage: ./caesar <numeric key>\n");
        return 1;
    }

    // Converting the key from string to int
    int key = atoi(argv[1]);

    // Getting user input
    string plain = get_string("plaintext:  ");

    // Printing encrypted text
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plain); i < n; i++)
    {
        printf("%c", rotate(plain[i], key));
    }
    printf("\n");

}

bool only_digits(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isdigit(s[i]) == 0)
        {
            return false;
        }
    }
    return true;
}

char rotate(char c, int a)
{
    char upper[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char lower[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int p;

    if (isalpha(c))
    {
        for (int i = 0; i < 26; i++)
        {
            if (upper[i] == c)
            {
                p = (i + a) % 26;
                return upper[p];
                break;
            }
            else if (lower[i] == c)
            {
                p = (i + a) % 26;
                return lower[p];
                break;
            }
        }
    }
    else
    {
        return c;
    }

    return c;
}