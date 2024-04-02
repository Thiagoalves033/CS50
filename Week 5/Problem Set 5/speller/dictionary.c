// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Global size variable
int word_count = 0;

// TODO: Choose number of buckets in hash table
const unsigned int N = 17576;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Obtaining the hash value
    int index = hash(word);
    node *ptr = table[index];

    if (ptr == NULL)
    {
        return false;
    }

    for (int i = 0; ptr != NULL; i++)
    {

        if (strcasecmp(word, ptr->word) == 0)
        {
            return true;
        }
        else
        {
            ptr = ptr->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // Function I created: Read the first three letters.
    // Time in total: ~ 1.10
    if (strlen(word) > 2)
    {
        return ((toupper(word[0]) - 'A') * 676 + (toupper(word[1]) - 'A') * 26 + toupper(word[2]) - 'A');
    }
    else if (strlen(word) == 2)
    {
        return ((toupper(word[0]) - 'A') * 26 + toupper(word[1]) - 'A');
    }
    else
    {
        return toupper(word[0]) - 'A';
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the dictionary file
    FILE *input;

    if (dictionary == NULL)
    {
        return false;
    }
    else
    {
        input = fopen(dictionary, "r");
    }

    // Read the words
    char buffer[LENGTH];
    while (fscanf(input, "%s", buffer) != EOF)
    {
        // Keeping track of how many times the loop happens (useful for size function)
        word_count++;

        // Creating a new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // Copying the word into the 'word value' in the node
        strcpy(n->word, buffer);

        // Node pointer to NULL
        n->next = NULL;

        // Insert word into the hash table
        int index = hash(buffer);
        n->next = table[index];
        table[index] = n;
    }

    // Closing the dictionary file
    fclose(input);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];

        for (int j = 0; ptr != NULL; j++)
        {
            node *tmp = ptr;
            ptr = ptr->next;
            free(tmp);
        }
    }

    return true;
}