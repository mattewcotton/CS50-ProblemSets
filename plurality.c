#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    //Try to find candidate with given name within candiates
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            //If candiate is found add 1 to their vote tally and return true
            candidates[i].votes++;
            return true;
        }
    }
    //If candidate us not found return false
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    //Declare variable for the higest vote position and value of the highest vote
    int highestVote = 0;
    bool highestPosition[MAX] = {false};
    //Search through the candidates to find the higest vote count
    for (int i = 0; i < candidate_count; i++)
    {
        //Check if current candidate has a higher vote tally then the previous highest
        if (candidates[i].votes > highestVote)
        {
            //Set highest votes variable to current vote tally
            highestVote = candidates[i].votes;
            //Loop to set all values of highest position array to false
            for (int j = 0; j < candidate_count; j++)
            {
                highestPosition[j] = false;
            }
            //Set position of this candidate in the array to true
            highestPosition[i] = true;
        }
        //Check if current candidate is equal to the previous highest
        else if (candidates[i].votes == highestVote)
        {
            highestPosition[i] = true;
        }
    }

    //Using the highest position array print the winning candidate names
    for (int i = 0; i < candidate_count; i++)
    {
        //Check if current highest position true, if so print candidates name
        if (highestPosition[i])
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}

