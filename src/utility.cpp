#include "../include/utility.h"
#include <algorithm>

int rand(int first, int second)
{
    if (first < second)
        return first + rand() % (second - first + 1);
    else
        return second + rand() % (first - second + 1);
}

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
            std::swap(numbers[i],numbers[index]);
            i++;
            j++;
        }
    }
}
