#ifndef UTILITY_H
#define UTILITY_H
#include <cstdlib>
#include <ctime>

int rand(const int first, const int second);
// It returns a random integer between first and second (or viceversa if second < first)
// Precondition: the function srand(time(NULL)) should be called before using this method

void generateKPermutation(int array[], const int first, const int last, const int k);
// Given an array, a range of numbers and a number k, it stores a k-permutation of the numbers 
// between first and last (included) in the array
// The size of the array must be at least k, otherwise a segmentation fault error will occurr
// Complexity: O(n)

#endif
