#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool find_cycle(int a, int b); // Function I created to auxiliate lock_pairs with recursion.
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // ranks[] is the index of the candidate who is the ith preference for the voter
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // Avoid getting points over itself and higher ranked candidates
            if (j > i)
            {
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // Only add the pairs in which a clear winner is declared
            // Just ignore ties.
            if (preferences[i][j] > preferences[j][i])
            {
                pair_count++;
                pairs[pair_count - 1].winner = i;
                pairs[pair_count - 1].loser = j;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Bubble sort pairs[]
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count - 1 - i; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j + 1].winner][pairs[j + 1].loser])
            {
                pair x = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = x;
            }
        }
    }

}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // bool locked[MAX][MAX]; locked[i][j] means i is locked in over j
    // If locked[A][B] and locked[C][A] exists, locked[B][C] shouldn't
    // Similarly, if locked[A][C] and locked[C][D] exists, locked[D][A] shouldn't
    // So, it can be said that 'A winner can't lose to his loser's loser'.
    for (int i = 0; i < pair_count; i++)
    {
        if (find_cycle(pairs[i].winner, pairs[i].loser) == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Function to make lock_pairs work recursively
bool find_cycle(int a, int b)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Base Case: When should the recursion stop? When there's no winning elements. Look for b, if found return true
        if (locked[b][i] == true && locked[i][a] == true)
        {
            return true;
        }

        // Recursive Case: Check who are the winning elements
        else if (locked[i][a] == true)
        {
            return find_cycle(i, b);
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // The winner is the one with no edges pointing towards him, in other words, is the winner who is never a loser

    for (int i = 0; i < candidate_count; i++)
    {
        bool winner = true;
        // Is candidate i a winner?
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == true)
            {
                winner = true;
                break;
            }
            else
            {
                winner = false;
            }
        }

        // Has this winner ever lost?
        if (winner == true)
        {
            for (int n = 0; n < candidate_count; n++)
            {
                if (locked[n][i] == true)
                {
                    winner = false;
                    break;
                }
            }
        }

        // If the winner is still true until here, print it
        if (winner == true)
        {
            printf("%s\n", candidates[i]);
        }
    }
}