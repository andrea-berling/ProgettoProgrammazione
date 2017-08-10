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

#endif
