#ifndef UTILITY_HPP
#define UTILITY_HPP
#include <cstdlib>
#include <ctime>

int rand(int first, int second)
{
    srand(time(NULL));
    if (first < second)
        return first + rand() % (second - first + 1);
    else
        return second + rand() % (first - second + 1);
}

#endif
