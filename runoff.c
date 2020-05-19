#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    //Cycle through all candiataes
    for (int i = 0; i < candidate_count; i++)
    {
        //Check if given name is a valid candidate
        if (strcmp(name, candidates[i].name) == 0)
        {
            //If name matches a candidate update the preferences array with voter's rank
            preferences[voter][rank] = i;
            return true;
        }
    }
    //No match so return false
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    //Cycle through all voters preferences and update vote tally if they have not yet been elimiated
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            //If the current candidate ranked in position j is not eliminated then add to their vote tally
            if (!candidates[preferences[i][j]].eliminated)
            {
                candidates[preferences[i][j]].votes++;
                j = candidate_count;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    //Cycle through the candidates and if they have a vote tally greater than the half the number of voters they win
    for (int i = 0; i < candidate_count; i++)
    {
        //Check vote tally for candidate i
        if (candidates[i].votes > (voter_count / 2))
        {
            //Print winning candidates name
            printf("%s\n", candidates[i].name);
            return true;
        }
    }

    //No cadidate has over half of the votes so return false
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    //Declare a variable to store the lowest vote tally
    int min = voter_count;
    //Cycle through each candidates vote tally to find the lowest
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes < min && !candidates[i].eliminated)
            min = candidates[i].votes;
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    //Cycle through candidate to check if all candidates have the "min" vote tally
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes != min && !candidates[i].eliminated)
            return false;
    }
    //If above loop completes without returning flase then all candidates must have the same number of votes
    return true;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    //Cycle through all candidates to check which have the min number of votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes ==  min)
            candidates[i].eliminated = true;
    }
    return;
}