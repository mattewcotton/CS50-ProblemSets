#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int letterPosition(char letter);
char lower(char letter);

int main(int argc, string argv[])
{
    //Check if just 1 command line agrument was used
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //Set second command line argument equsal to key
    string key = argv[1];
    //Calculate key length
    int keyLength = strlen(key);
    //Check if key is 26 chars long
    if (keyLength != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    //Check if key contains non-alphabetic chars
    for (int i = 0; i < keyLength; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must contain only alphabetic characters.\n");
            return 1;
        }
    }
    //Check if key contains a letter more than once
    bool duplicateLetterCheck[26] = {false};
    int n;
    for (int i = 0; i < keyLength; i++)
    {
        n = letterPosition(key[i]);
        //When duplicate letter is found the value of the duplicate chack array will already be true
        if (duplicateLetterCheck[n] == true)
        {
            printf("Key must not duplicate letters.\n");
            return 1;
        }
        else
        {
            duplicateLetterCheck[n] = true;
        }
    }
    //Convert key to all lower case so that there is no confuision over case later in program
    for (int i = 0; i < keyLength; i++)
    {
        key[i] = lower(key[i]);
    }

    //Get plaintext input from user
    string plaintext = get_string("plaintext: ");
    //Calclate the length of plain text
    unsigned long plainLength = strlen(plaintext);
    //delcare output ciphertext output string
    char ciphertext[plainLength];
    //Declare current poisition variable
    int position;
    //Encipher plaintext
    for (int i = 0; i < plainLength; i++)
    {
        //Check if current character is alphabetic
        if (isalpha(plaintext[i]))
        {
            position = letterPosition(plaintext[i]);
            //Chack if current character is upper or lower case
            if (isupper(plaintext[i]))
            {
                //When plaintext char is upper case convert letter from key to upper case
                ciphertext[i] = toupper(key[position]);
            }
            else
            {
                //When plaintext char is lower case use key directly (as key is all lower case)
                ciphertext[i] = key[position];
            }
        }
        //When plaintext char is not aplhabetic add the value to the cipher unchanged
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    //Output ciphertext
    printf("ciphertext: ");
    for (int i = 0; i < plainLength; i++)
    {
        printf("%c", ciphertext[i]);
    }
    printf("\n");
    return 0;
}

//Function to return the position of a letter within the alphabet. Where;
// a or A = 0
// b or B = 1
// z or Z = 25
// Error = 26
int letterPosition(char letter)
{
    //Convert all inputs to lower case
    letter = lower(letter);
    //Use switch statement to return the correct position with the alphabet
    switch (letter)
    {
        case 'a':
            return 0;
        case 'b':
            return 1;
        case 'c':
            return 2;
        case 'd':
            return 3;
        case 'e':
            return 4;
        case 'f':
            return 5;
        case 'g':
            return 6;
        case 'h':
            return 7;
        case 'i':
            return 8;
        case 'j':
            return 9;
        case 'k':
            return 10;
        case 'l':
            return 11;
        case 'm':
            return 12;
        case 'n':
            return 13;
        case 'o':
            return 14;
        case 'p':
            return 15;
        case 'q':
            return 16;
        case 'r':
            return 17;
        case 's':
            return 18;
        case 't':
            return 19;
        case 'u':
            return 20;
        case 'v':
            return 21;
        case 'w':
            return 22;
        case 'x':
            return 23;
        case 'y':
            return 24;
        case 'z':
            return 25;
        default:
            return 26;
    }
}

char lower(char letter)
{
    //Convert all inputs to lower case
    if (isupper(letter))
    {
        letter = tolower(letter);
    }
    return letter;
}