//include the standard IO library, CS50 library, string library, and ctype library
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

//create main that takes no arguments
int main(void)
{
    //get a name from the user, and save it to the variable name
    string name = GetString();
    
    //print the first character of the name input in capital
    printf("%c", toupper(name[0]));
    
    //iterate through the string given
    for (int x = 1, n = strlen(name); x < n; x++)
    {
        //if the character currently being checked is a space, go to the next character and print it in uppercase
        if (name[x] == ' ')
        {
            x++;
            printf("%c", toupper(name[x]));
        }
    }
    
    //go to the next line
    printf("\n");
    
    return 0;
}