#ifndef UTILITY_HPP
#define UTILITY_HPP
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

int rand(int first, int second)
{
    if (first < second)
        return first + rand() % (second - first + 1);
    else
        return second + rand() % (first - second + 1);
}

template<typename T>
T pick(vector<T> args)
{
    int n = args.size() - 1;
    int index = rand(0,n);
    return args[index];
}

#endif
