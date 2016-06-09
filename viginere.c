//include the standard IO library, CS50 library, string library, and ctype library
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

//create main
int main(int argc, string argv[])
{
    //ensure proper useage
    if (argc != 2)
    {
        printf("Proper useage: ./viginere key\n");
        return 1;
    }
    
    //get the encryption key from the first argument (not including ./viginere)
    string key = (argv[1]);
    
    //iterate through the key and ensure it is all in lowercase
    for (int x = 0, n = strlen(key); x < n; x++)
    {
        key[x] = tolower(key[x]);
    }
    
    //get a message to encrypt from the user
    string message = GetString();
    
    //create a counter to iterate through the characters of the key provided
    int keycounter = 0;
    
    //iterate through the message and key character and change each alphabetical character accordingly
    for (int x = 0, n = strlen(message); x < n; x++)
    {
        //if the character is an alphabetical character, ecrypt it
        //otherwise, print it as is
        if (message[x] >= 'A' && message[x] <= 'Z')
        {
            //set the current character to be equal to the char value of the int value of the character plus the int value of the current character of the key, accounting for rolling over if it goes past Z
            message[x] = (char) (((int) message[x] + (int) key[keycounter] - (int) 'a' - (int) 'A') % 26 + (int) 'A');
            printf("%c", message[x]);
            
            //iterate through the character of the key
            keycounter++;
            
            //reset the key counter if it reaches the end
            if (keycounter >= strlen(key))
            {
                keycounter = 0;
            }
        }
        else if (message[x] >= 'a' && message[x] <= 'z')
        {
            //set the current character to be equal to the char value of the int value of the character plus the int value of the current character of the key, accounting for rolling over if it goes past z
            message[x] = (char) (((int) message[x] + (int) key[keycounter] - 2 * (int) 'a') % 26 + (int) 'a');
            printf("%c", message[x]);
            
            //iterate through the character of the key
            keycounter++;
            
            //reset the key counter if it reaches the end
            if (keycounter >= strlen(key))
            {
                keycounter = 0;
            }
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