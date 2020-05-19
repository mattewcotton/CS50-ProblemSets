#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    //Get input from user for the desired height of the pyramids
    //Use a do while loop to check input is between 1 and 8
    do 
    {
        height = get_int("How high would you like the pyramids to be (between 1 and 8)?\n");

    } 
    while (height < 1 || height > 8);

    //Use a for loop to create the 2 pyramids
    for (int i = 0; i < height; i++)
    {
        //Use a for loop to print height - 1 - i empty spaces to align the left pyramid correctly
        for (int j = 0; j < height - 1 - i; j++)
        {
            printf(" ");
        }

        //Use another for loop to print i + 1 blocks of the left pyramid
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        //Create gap between left and right pyramids
        printf("  ");

        //Use a for loop to print the blocks of the right pyramid
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        //Move cursor onto a new line before printing next row of blocks
        printf("\n");

    }
    //printf("\n");
}