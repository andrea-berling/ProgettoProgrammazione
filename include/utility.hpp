#ifndef UTILITY_H
#define UTILITY_H
#include <cstdlib>
#include <ctime>

// It returns a random integer between first and second (or viceversa if second < first)
// Precondition: the function srand(time(NULL)) should be called before using this method
inline int rand(int first, int second)
{
    if (first < second)
        return first + rand() % (second - first + 1);
    else
        return second + rand() % (first - second + 1);
}

// Given an array, a range of numbers and a number k, it stores a k-permutation of the numbers 
// between first and last (included) in the array
// The size of the array must be at least k, otherwise a segmentation fault error will occurr
// Complexity: O(n)
void generateKPermutation(int array[], int first, int last, int k)
{

    int d = last - first + 1;
    if (k <= d)
    {
        int i = 0,j=0;
        int numbers[d];
        int index;

        for(int i = 0; i < d; i++)
            numbers[i] = i;


        while(i < k)
        {
            index = rand(i,d-1);
            array[j] = numbers[index];
            swap(numbers[i],numbers[index]);
            i++;
            j++;
        }
    }
}


#endif
