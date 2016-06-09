/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

//all memory required will be assigned using malloc() so that it can later be returned using free() to eliminate memory leaks

//create a trie structure for loading the dictionary into
struct trie
{
    //use a boolean to determine whether or not a word ends at this node
    bool end;
    
    //create an array of pointers to other trie nodes
    struct trie* child[27];
};

//create a pointer to a trie which will be used as the root node
struct trie* root;;

//create a pointer to a trie
//this will be used to traverse back to the root's address when a new word is to be loaded
struct trie* currentaddress;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    //set the currentaddress to root to begin nagivating through the trie
    currentaddress = root;
    
    //create an index variable to check if the path of the word we are looking for exists and
    //if the path can terminate (end == true) at the end of the given word
    int index;
    
    //iterate through the word checking each character and traversing/navigating the trie
    for (int x = 0, length = strlen(word); x < length; x++)
    {
        //convert the current character being checked lowercase and then to the index value used for loading
        //if the character read in is a letter from a to z, set it to be 0 to 25 accordingly
        if ((int)tolower(word[x]) >= (int)'a' && (int)tolower(word[x]) <= (int)'z')
        {
            index = (int)tolower(word[x]) - (int)'a';
        }
        //if the character read in is an apostrophe, set the index to be 26
        else if (word[x] == '\'')
        {
            index = 26;
        }
        //otherwise the character is not valid and the word must be invalid, therefore return false
        else
        {
            return false;
        }
        
        //check if that path exists, if it does not then the word must be invalid
        if (currentaddress -> child[index] == NULL)
        {
            return false;
        }
        //otherwise move on to that child node
        else
        {
            currentaddress = currentaddress -> child[index];
        }
    }
    
    //since strlen returns the value of the word up until but not including the terminating character,
    //we will now check if the word can terminate at this node. if it can, return true, otherwise return false
    //to do this we will simply return the value of the end boolean of the currentaddress, since both false and NULL will return as false
    return currentaddress -> end;
}

//create a helper function to navigate the trie and insert characters
void modifytrie(int i)
{
    //if the index passed to us is 27, this indicates that it is the end of a word
    //set the end variable of the current node to be true, and set the current node
    //to be the root
    if (i == 27)
    {
        currentaddress -> end = true;
        currentaddress = root;
    }
    //otherwise our index must be between 0 and 26
    else
    {
        //if this letter/index already exists, change the address of currentaddress to it
        if (currentaddress -> child[i] != NULL)
        {
            currentaddress = currentaddress -> child[i];
        }
        //if it does not exist, allocate memory for a child node and change the address of 
        //currentaddress to it
        else
        {
            currentaddress -> child[i] = (struct trie *) malloc(sizeof(struct trie));
            currentaddress = currentaddress -> child[i];
        }
    }
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    //allocate memory for root to initalize it
    root = (struct trie*) malloc(sizeof(struct trie));
    
    //set currentaddress to be the root's address
    currentaddress = root;
    
    //open the dictionary file for reading
    FILE *file = fopen(dictionary, "r");
    
    //seek to the end of the file and record it's size
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    
    //seek back to the beginning of the file
    fseek(file, 0, SEEK_SET);
    
    //create variables c and index, c will hold the current character of the file stream and index
    //will be used to give the characters a numeric value to navigate the trie
    char c;
    int index;
    
    //iterate through the file until you reach the end of file
    while (ftell(file) < size)
    {
        
        //read in a character from the file
        fread(&c, sizeof(char), sizeof(char), file);
        
        //if the character read in is a letter from a to z, set it to be 0 to 25 accordingly
        if ((int)c >= (int)'a' && (int)c <= (int)'z')
        {
            index = (int)c - (int)'a';
        }
        //if the character read in is an apostrophe, set the index to be 26, this will be the last available path in our trie
        else if (c == '\'')
        {
            index = 26;
        }
        //if the character read in is the newline character, set the index to be 27, this will tell the helper
        //function to set the current node's end boolean to be true, indicating the end of a word and to seek back to the root of the trie
        else if (c == '\n')
        {
            index = 27;
        }
        //if the character is not a newline character, an apostrophe, or any letter from a to z, the
        //function will fail to load, return false
        else
        {
            return false;
        }
        
        //pass the index to our helper function which will handle insertion of characters into our trie
        modifytrie(index);
    }
    
    //if the code reaches this part, the entirety of the dictionary has been loaded
    return true;
}

//recursive helper function for finding the size of the dictionary
int sizeRecursive(struct trie* address)
{
    //create a variable to store the number of words in all the children of this node
    int total = 0;
    
    //recursively call each node
    for (int x = 0; x < 27; x++)
    {
        if (address -> child[x] != NULL)
        {
            total += sizeRecursive(address -> child[x]);
        }
    }
    
    //if this node is the end of a word, add one to the total
    if (address -> end == true)
    {
        total++;
    }
    
    //return the total
    return total;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    //in order to not change the way main operates, this method will simply redirect to the recursive helper function for finding size
    
    currentaddress = root;
    return sizeRecursive(currentaddress);
}

//recursive helper function for the unload function, traverses the trie bottom up, left to right
void unloadRecursive(struct trie* address)
{
    //call unloadRecursive on every child that exists, if any, then unloads itself
    for (int x = 0; x < 27; x++)
    {
        if (address -> child[x] != NULL)
        {
            unloadRecursive(address -> child[x]);
        }
    }
    
    free(address);
    
    return;
}
/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    currentaddress = root;
    unloadRecursive(currentaddress);
    return true;
}
