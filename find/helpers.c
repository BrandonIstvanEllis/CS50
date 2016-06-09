/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    //base case, if the array we are passed is size 1, check the only value, if it is the value we are
    //looking for, return true. otherwise, return false
    if (n == 1)
    {
        if (values[0] == value)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    //create the variable middlevalue, for later use
    float middlevalue;
    
    //if the array we are passed is an odd number of values, go to the middle and check if it is the value we are looking for
    //if it is not the value we are looking for, save the value to the middlevalue variable for later use
    if (n % 2 != 0)
    {
        if (values[n / 2] == value)
        {
            return true;
        }
        else
        {
            middlevalue = values[n / 2];
        }
    }
    //otherwise if the array we are passed is an even number of values, check the middle two values if either is the value we are looking for
    //if neither is the value we are looking for, save the average of the two numbers to the middlevalue variable for later use
    else
    {
        if (values[n / 2 - 1] == value || values[n / 2] == value)
        {
            return true;
        }
        else
        {
            middlevalue = (values[n / 2 - 1] + values[n / 2]) / 2.0;
        }
    }
    
    //create two arrays, the first equal to half the length of the array we were passed, rounded up
    //the other array equal to the other half of the array we were passed, rounded down
    int firsthalf[n / 2 + n % 2];
    int secondhalf[n / 2];
    
    //assign the respective values of each half to the arrays
    for (int x = 0; x < n / 2 + n % 2; x++)
    {
        firsthalf[x] = values[x];
    }
    for (int x = n / 2 + n % 2; x < n; x++)
    {
        secondhalf[x - n / 2 - n % 2] = values[x];
    }
    
    //if the middlevalue is greater than the value we are looking for, search in the left half of the array
    //otherwise, search for the value in the right half of the array
    if (middlevalue > value)
    {
        return search(value, firsthalf, n / 2 + n % 2);
    }
    else
    {
        return search(value, secondhalf, n / 2);
    }
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    //create a temporary variable to store values of the array when swapping
    int temp;
    
    //iterate through the list, comparing values and swapping them, if no swaps are made the loop will end
    //the loop terminates if x reaches n - 1, since the last value does not have any value to the right of it to compare to
    for (int x = 0; x < n - 1; x++)
    {
        //if the current value in the array is larger than the next value in the array, swap them, then set x to -1 to sort through the list from the beginning
        if (values[x] > values[x+1])
        {
            temp = values[x];
            values[x] = values[x+1];
            values[x + 1] = temp;
            x = -1;
        }
    }
    
    return;
}