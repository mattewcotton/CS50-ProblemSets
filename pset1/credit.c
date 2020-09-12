#include <stdio.h>
#include <cs50.h>

int cardTypeCheck(int cardNoArr[16]);
bool checkChecksum(int cardNoArr[16]);

int main(void)
{
    //Get user to enter credit card number
    long cardNo = get_long("Enter card number without spaces or hyphens: ");

    //Split card number into each digit
    int cardNoArr[16];
    //Use for loop to build card number array
    //Card number position format:
    // [16][15][14][13[]12]...[3][2][1][0]
    long temp = cardNo;
    for (int i = 0; i < 16; i++)
    {
        cardNoArr[i] = temp % 10;
        temp = temp / 10;
        //Debug code
        //printf("%i\n", cardNoArr[i]);
    }

    //Check if this credit card number is Amex, Visa or Mastercard
    int type = cardTypeCheck(cardNoArr);

    //If returned type is INVALID then print Invalid and end program here
    if (type == 0)
    {
        printf("INVALID\n");
        return 0;
    }

    //Check if the checksum us valid
    //If valid print the card type (Amex, Visa or Mastercard)
    //If invlaid print "INVALID"
    if (checkChecksum(cardNoArr) == true)
    {
        //Print card type
        if (type == 1)
        {
            printf("AMEX\n");
        }
        else if (type == 2)
        {
            printf("MASTERCARD\n");
        }
        else if (type == 3)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

//Function to check credit card type
//return mapping:
//              0 - INVALID
//              1 - AMEX
//              2 - MASTERCARD
//              3 - VISA
int cardTypeCheck(int cardNoArr[16])
{
    //For Amex cards length is 15 digits and card number starts with 34 or 37
    if (cardNoArr[14] == 3 && (cardNoArr[13] == 4 || cardNoArr[13] == 7)
        && cardNoArr[15] == 0)
    {
        return 1;
    }
    //For Mastercard cards length is 16 digits and card number starts with 51, 52, 53, 54 or 55
    else if (cardNoArr[15] == 5 && (cardNoArr[14] == 1 || cardNoArr[14] == 2
        || cardNoArr[14] == 3 || cardNoArr[14] == 4 || cardNoArr[14] == 5))
    {
        return 2;
    }
    //For Visa cards length is 13 or 16 digits and card number starts with 4
    else if (cardNoArr[15] == 4 || (cardNoArr[12] == 4 && (cardNoArr[13] == 0
        && cardNoArr[14] == 0 && cardNoArr[15] == 0)))
    {
        return 3;
    }
    //If none of the aboce conditions are met then the card number is invalid
    else
    {
        return 0;
    }
}

//Function to calculate the checksum of the card number
bool checkChecksum(int cardNoArr[16])
{
    //multiply every other digit by 2 starting with the 2nd number ([1]))
    int sum = 0;
    int temp;
    for (int i = 1; i < 16; i += 2)
    {
        temp = cardNoArr[i] * 2;

        //Check if temp is one or two digits
        if (temp < 10)
        {
            sum += temp;
        }
        else
        {
            sum += 1 + (temp % 10);
        }
    }

    //Add the digits that were not multiplied by 2
    for (int i = 0; i < 16; i += 2)
    {
        sum += cardNoArr[i];
    }

    //Check if the modulo of the sum is equal to zero
    if (sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }

}