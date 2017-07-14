#ifndef UTILITY_H
#define UTILITY_H
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// It returns a random integer between first and second (or viceversa if second < first)
// Precondition: the function srand(time(NULL)) should be called before using this method
inline int rand(int first, int second)
{
    if (first < second)
        return first + rand() % (second - first + 1);
    else
        return second + rand() % (first - second + 1);
}

// Given a vector of elements, it picks one randomly and returns it
template<typename T> 
T pick(vector<T> args)
{
    int n = args.size() - 1;
    int index = rand(0,n);
    return args[index];
}

#endif
