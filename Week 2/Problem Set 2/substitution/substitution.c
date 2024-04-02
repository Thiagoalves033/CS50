#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char rotate(char c);

char alpha[26];

int main(int argc, string argv[])
{
    // Correct usage
    if (argc != 2)
    {
        printf("Usage: ./substitution <key>\n");
        return 1;
    }

    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (n != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        else if (isalpha(argv[1][i]) == 0)
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }

        // Check if the character is repeated
        for (int j = 0; j < n; j++)
        {

            if (alpha[j] == argv[1][i])
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }

        // Assign the characters to alpha array
        alpha[i] = argv[1][i];
    }

    // User input
    string plain = get_string("plaintext:  ");

    // Printing encrypted text
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plain); i < n; i++)
    {
        printf("%c", rotate(plain[i]));
    }
    printf("\n");

}

char rotate(char c)
{
    char upper[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char lower[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    for (int i = 0; i < 26; i++)
    {
        if (upper[i] == c)
        {
            c = toupper(alpha[i]);
            return c;
            break;
        }
        else if (lower[i] == c)
        {
            c = tolower(alpha[i]);
            return c;
            break;
        }
    }
    return c;
}