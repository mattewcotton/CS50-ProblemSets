//includes standard input/output library and cs50 library
#include <stdio.h>
#include <cs50.h>

int main(void) 
{
    //Get users name 
    string name = get_string("What is your name?\n");
    //Print hello with users name
    printf("Hello, %s\n", name);
    printf("Hello again\n");
}