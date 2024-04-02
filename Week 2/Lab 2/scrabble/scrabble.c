#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else if (score1 == score2)
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    int p = 0;
    int LETTERS[] = {65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90};

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        char c = word[i];

        // If uppercase, the points are the same as lowercase
        if (islower(c) != 0)
        {
            c -= 32;
        }

        // Compare 'c' value with LETTERS array and figure which index does it corresponds to
        // Associate LETTERS[index] to POINTS[index] and sum
        int index;
        for (index = 0; index < 26; index++)
        {
            if (LETTERS[index] == c)
            {
                p = p + POINTS[index];
                break;
            }
        }
    }

    return p;
}
