#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string s);
int count_words(string s);
int count_sentences(string s);

int main(void)
{
    // Getting user input
    string text = get_string("Text: ");

    // Number of letters, words and sentences
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Averages
    float L = letters / (float) words * 100;
    float S = sentences / (float) words * 100;

    // Coleman-Liau index
    float index = 0.0588 * L - 0.296 * S - 15.8;

    // Printing the grade
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }

}

int count_letters(string s)
{
    int n = strlen(s);
    int h = n;

    for (int i = 0; i < n; i++)
    {
        if (isspace(s[i]) != 0)
        {
            h--;
        }
        else if (ispunct(s[i]) != 0)
        {
            h--;
        }
    }
    return h;
}

int count_words(string s)
{
    int n = strlen(s);
    int h = 1;

    for (int i = 0; i < n; i++)
    {
        if (isspace(s[i]) != 0)
        {
            h++;
        }
    }
    return h;
}

int count_sentences(string s)
{
    int n = strlen(s);
    int h = 0;

    for (int i = 0; i < n; i++)
    {
        if (s[i] == '.')
        {
            h++;
        }
        else if (s[i] == '!')
        {
            h++;
        }
        else if (s[i] == '?')
        {
            h++;
        }
    }
    return h;
}