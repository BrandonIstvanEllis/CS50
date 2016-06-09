//include standard IO library and the CS50 library
#include <stdio.h>
#include <cs50.h>

//create main that takes no arguments
int main(void)
{
    //print out "minutes: ", prompting the user to enter the number of minutes spent in the shower
    printf("minutes: ");
    
    //get an integer from the user using the GetInt() function, and multiply it by 12 to calculate number of bottles used, then save this value to the bottles variable
    int bottles = GetInt() * 12;
    
    //print out the number of bottles used for the shower
    printf("bottles: %i\n", bottles);
    
    return 0;
}