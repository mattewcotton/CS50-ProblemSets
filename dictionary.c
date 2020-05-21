// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

//Declare variable for dictionary size
unsigned int dicSize = 0;

// Number of buckets in hash table
const unsigned int N = 5490;

// Hash table
node *table[N];

//Define clearLinkedLinstFunction
void clearLinkedList(node *n);

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //Hash word
    int h = hash(word);

    //Loop through all nodes in linked list for h (hash value of word)
    for (node *trav = table[h]; trav != NULL; trav = trav->next)
    {
        if (strcasecmp(word, trav->word) == 0)
            return true;

    }
    //Reached the end of the function without finding the word therefore retunr false
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 0;
    unsigned int length = strlen(word);

    for (int i = 0; i < length; i++)
    {
        char c = tolower(word[i]);
        hash += c;
    }
    return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //Open dictionary file
    FILE *dic = fopen(dictionary, "r");

    //Check if dictionary was opened successfully
    if (dic == NULL)
        return false;

    //Set dictionary size counter to zero
    dicSize = 0;

    //Dynamically allocate space for a word from the dictionary up to max word length LENGTH + 1
    char *word = malloc((LENGTH + 1) * sizeof(char));

    //Loop through until end of the file is reached
    while (true)
    {
        //Read strings from dictioary one at a time
        int i = fscanf(dic, "%s", word);
        //Break if word == EOF
        if (i == EOF)
            break;

        //Create a new node for each word
        node *n = malloc(sizeof(node));
        //Check if dynamic allocation was successful
        if (n == NULL)
            return false;

        //Copy word into new node and set next pointer to NULL
        strcpy(n->word, word);
        n->next = NULL; //Is this needed given the reallocation of next below?

        //Hash word to obtain a hash value
        int h = hash(word);

        //Insert node into hash table at that location
        n->next = table[h];
        table[h] = n;

        //Increment dictionary size
        dicSize++;
    }

    //Close dictionary
    fclose(dic);

    //Free word
    free(word);

    //Function ran until the end without any errors so return true
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    //Return the count of words in dictionary that was calculated during load call
    return dicSize;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //Cycle through all nodes in table
    //Use recursion to unload
    for (int i = 0; i < N; i++)
    {
        clearLinkedList(table[i]);
    }

    return true; //???
}

void clearLinkedList(node *n)
{
    //base case
    if (n == NULL)
    {
        return;
    }
    //Call clearLinkedList for next node
    clearLinkedList(n->next);

    //Free this node
    free(n);
}
