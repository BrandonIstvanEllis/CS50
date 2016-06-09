//include the standard IO library and the CS50 library
#include <stdio.h>
#include <cs50.h>

//create main that takes no arguments
int main(void)
{
    //create the height variable to store the height, an integer from 0 to 23 input by the user
    int height;
    
    //get the input from the user, and repeatedly prompt and get the input until the user enters a number between 0 and 23
    do
    {
        //promt the user for the height and assign input height to the variable height
        printf("height: ");
        height = GetInt();
    }
    while(height < 0 || height > 23);
    
    //print the half-pyramid
    for (int x = 0; x < height; x++)
    {
        //print the spacing for this level of the half-pyramid
        for (int y = 1; y < height - x; y++)
        {
            printf(" ");
        }
        
        //print this level of the half-pyramid
        for (int y = 0; y < x + 1; y++)
        {
            printf("#");
        }
        
        //print the last hash and go to the next line
        printf("#\n");
    }
    
    return 0;
}