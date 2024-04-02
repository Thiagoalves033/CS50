// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

string replace(string s);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf (" Use: ./no-vowels <input>\n");
        return 1;
    }

    printf("%s\n", replace(argv[1]));
}

string replace(string s)
{

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        char c = tolower(s[i]);

        switch (c)
        {
        case 'a':
            s[i] = '6';
            break;

        case 'e':
            s[i] = '3';
            break;

        case 'i':
            s[i] = '1';
            break;

        case 'o':
            s[i] = '0';
            break;

        default:
            s[i] = c;
            break;
        }
    }
    return s;
}