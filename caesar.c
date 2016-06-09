//include the standard IO library, CS50 library, and string library
#include <stdio.h>
#include <cs50.h>
#include <string.h>

//create main
int main(int argc, string argv[])
{
    //ensure proper useage
    if (argc != 2)
    {
        printf("Proper useage: ./caesar key\n");
        return 1;
    }
    
    //get the encryption key from the first argument (not including ./caesar)
    int key = atoi(argv[1]);
    
    //get a message to encrypt from the user
    string message = GetString();
    
    //iterate through the message and change each alphabetical character
    for (int x = 0, n = strlen(message); x < n; x++)
    {
        //if the character is an alphabetical character, ecrypt it
        //otherwise, print it as is
        if (message[x] >= 'A' && message[x] <= 'Z')
        {
            //set the current character to be equal to the char value of the int value of the character plus the key, accounting for rolling over if it goes past Z
            message[x] = (char) (((int) message[x] + key - (int) 'A') % 26 + (int) 'A');
            printf("%c", message[x]);
        }
        else if (message[x] >= 'a' && message[x] <= 'z')
        {
            //set the current character to be equal to the char value of the int value of the character plus the key, accounting for rolling over if it goes past z
            message[x] = (char) (((int) message[x] + key - (int) 'a') % 26 + (int) 'a');
            printf("%c", message[x]);
        }
        else
        {
            //print the current character as is
            printf("%c", message[x]);
        }
    }
    
    //go to the next line
    printf("\n");
    
    return 0;
}