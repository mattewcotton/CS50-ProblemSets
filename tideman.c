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
//Declare a boolean to be set and returned
bool cycle = true;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void cycleCheck(int cnt);

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
    //Cycle through all of the candidates to check if the argument name is a valid candidate
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            //Update ranks[i] to incidate this cadidate (name) is the voters i'th preference
            ranks[rank] = i;
            //Return true as a match was found
            return true;
        }
    }
    //No candidate of this name found therefore return false
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    //For each candidate check if all other candidates are above or below in the rank
    //Change the preferences array accordingly
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i == j)
            {
                //Do nothing as this is the same candidate for i and j values
            }
            else
            {
                //Search through ranks to find if i or j is ranked higher
                for (int r = 0; r < candidate_count; r++)
                {
                    if (ranks[r] == i)
                    {
                        //candidate i has been found first so add 1 to the preferences [i][j]
                        preferences[i][j]++;
                        //end this (r) for loop now as i has been found
                        r = candidate_count;
                    }
                    else if (ranks[r] == j)
                    {
                        //Candidate j has been found first. Do not add to preferences [j][i] as this will duplicate the count
                        //End r loop now
                        r = candidate_count;
                    }
                }
            }
            //Debug code
            //printf("i: %i j: %i Pref: %i\n", i, j, preferences[i][j]);
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //Set pair_count to zero
    pair_count = 0;
    //Cycle through the preferences array to find where one candidate is prefered to another
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            //else:
            //Do nothing as when [j][i] is greater than [i][j] will be covered later in the loop
            //And equals situations will be ignored

        }
    }
    //Debug code
    /*for (int i = 0; i < pair_count; i++)
    {
        printf("Winner: %i Loser: %i\n", pairs[i].winner, pairs[i].loser);
    }*/

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{

    //Create an structure to store the winning margins for each pair
    typedef struct
    {
        int pairIndex;
        int winMargin;
    }
    pairWinMargin;

    //Declare a win margin array
    pairWinMargin pairWinMargins[MAX];

    //Add pairs data to array and calculate min margins
    for (int i = 0; i < pair_count; i++)
    {
        pairWinMargins[i].pairIndex = i;
        pairWinMargins[i].winMargin = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
    }

    //Declare required temporary variables
    pairWinMargin tempWinMargin;
    bool swapDone;
    //Sort pairWinMargins array - Bubble algorithm
    for (int i = 0; i < pair_count; i++)
    {
        swapDone = false;
        for (int j = 0; j < pair_count; j++)
        {
            if (pairWinMargins[j + 1].winMargin > pairWinMargins[j].winMargin)
            {
                tempWinMargin = pairWinMargins[j + 1];
                pairWinMargins[j + 1] = pairWinMargins[j];
                pairWinMargins[j] = tempWinMargin;
                swapDone = true;
            }
        }
        if (swapDone == false)
        {
            i = pair_count;
        }
    }

    //Declare a temporary pair array
    pair tempPairs[MAX * (MAX - 1) / 2];
    //Check order of pairs array based on sorted pairWinMargin array
    for (int i = 0; i < pair_count; i++)
    {
        tempPairs[i] = pairs[pairWinMargins[i].pairIndex];
    }
    //Set pairs array equal to the sorted values
    for (int i = 0; i < pair_count; i++)
    {
        pairs[i] = tempPairs[i];
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //Cycle through the sorted pairs array and set locked pairs array
    for (int i = 0; i < pair_count; i++)
    {
        //Set locked value for pair[k] to true
        locked[pairs[i].winner][pairs[i].loser] = true;

        //Check if locked array with latest change contains any cycles/loops
        cycleCheck(candidate_count);

        //If the cycle is now set to false then a cycle has been detected and the current pair needs to be unlocked
        if (cycle == false)
        {
            //Set locked value for pair[k] to true
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
        cycle = true;
    }
    return;
}

//Check if the current version of the locked array contains any cycles/arrays
void cycleCheck(int cnt)
{
    if (cnt == 0)
    {
        return;
    }

    int r = 0;
    bool rank[cnt];
    //Set all values of rank array to false
    for (int i = 0; i < cnt; i++)
    {
        rank[i] = false;
    }

    //Use recursion to call cycleCheck() unitl cnt = 0
    cycleCheck(cnt - 1);

    //sent rank array to true where locked array values are true
    for (int i = 0; i < cnt; i++)
    {
        for (int j = 0; j < cnt; j++)
        {
            if (locked[i][j] == true)
            {
                rank[i] = true;

            }
        }
    }

    //Count the number of true values within the rank array
    for (int i = 0; i < cnt; i++)
    {
        if (rank[i] == true)
        {
            r++;
        }
    }

    //If r is equal to cnt then return false
    if (r == cnt)
    {
        cycle = false;
    }
}

// Print the winner of the election
void print_winner(void)
{
    //Declare a winner variables for the winner candidate index
    int winner;
    //Search the locked array for a column that is all false
    for (int j = 0; j < candidate_count; j++)
    {
        //Declare counter for number of false in one column
        int false_count = 0;
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][j] == false)
            {
                false_count++;
            }
        }
        if (false_count == candidate_count)
        {
            winner = j;
            j = candidate_count;
        }
    }

    //Print highest locked count (winner)
    printf("%s\n", candidates[winner]);
    return;
}