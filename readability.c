#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

unsigned long count_letters(string text);
unsigned long count_words(string text);
unsigned long count_sentences(string text);

int main(void)
{
    //Get text input from user
    string text = get_string("Text: ");

    //Count the number of letters in the text
    unsigned long letters = count_letters(text);

    //Count the number of words
    unsigned long words = count_words(text);

    //Count the number of sentences
    unsigned long sentences = count_sentences(text);

    //Calculate the Coleman-Liau index
    float index = (0.0588 * ((float) letters / (float) words) * 100) - (0.296 * ((float) sentences / (float) words) * 100) - 15.8;

    //Check if the index is less than 1, greater than or equal to 16 or any number in between
    //then print the correct output
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %1.0f\n", index);
    }
}

//Funtion to count the number of letters in the text
unsigned long count_letters(string text)
{
    //Declare variable for the number of letters
    unsigned long letters = 0;
    //Loop to count the number of letters
    for (unsigned long i = 0, n = strlen(text); i < n; i++)
    {
        //Check if each character in the string is a lower or upper case letter
        if (isupper(text[i]) || islower(text[i]))
        {
            letters++;
        }
    }
    //Return number of letters
    return letters;
}

//Function to count the number of words in text
unsigned long count_words(string text)
{
    //check if the string includes at least 1 char
    //If the string length is zero then return words as zero
    unsigned long n = strlen(text);
    if (n == 0)
    {
        return 0;
    }
    //Declare variable for words
    unsigned long words = 1;
    //Use a loop to count the number of words
    for (int i = 0; i < n; i++)
    {
        //Check if each character in the strin is a space
        if (isblank(text[i]))
        {
            words++;
        }
    }
    //Return word count
    return words;
}

//Count the number of sentences
unsigned long count_sentences(string text)
{
    //Declare vairiable for number of sentences
    unsigned long sentences = 0;
    //Count the number of sentences (based only on the number of full stops, exclamation marks and question marks)
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        //Check if the char is a ".", "!" or "?"
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    //Return the sentence count
    return sentences;
}