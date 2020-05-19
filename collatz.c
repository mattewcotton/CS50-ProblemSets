#include <stdio.h>

int collatz(int n);

int main(void)
{
    //Call collatz funtion
    printf("%i\n", collatz(1));
    printf("%i\n", collatz(2));
    printf("%i\n", collatz(3));
    printf("%i\n", collatz(4));
    printf("%i\n", collatz(5));
    printf("%i\n", collatz(6));
    printf("%i\n", collatz(7));
    printf("%i\n", collatz(8));
    printf("%i\n", collatz(15));
    printf("%i\n", collatz(27));
    printf("%i\n", collatz(50));
}

int collatz(int n)
{
    //Print n
    //printf("%i\n", n);
    //Base case
    if (n == 1)
    {
        return 0;
    }

    //Recursion case 1: n is even
    if (n % 2 == 0)
        return 1 + collatz(n / 2);
    //Recursion case 2 \: n is odd
    else
        return 1 + collatz((3 * n) + 1);
}