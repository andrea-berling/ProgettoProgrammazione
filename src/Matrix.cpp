#ifndef MATRIX_CPP
#define MATRIX_CPP
#include "../include/Matrix.h"

template<typename T>
Matrix<T>::Matrix()
{
    matrix = nullptr;
    cols = rows = -1;
}
// Defualt constructor

template<typename T>
Matrix<T>::Matrix(int rows, int cols) : rows(rows), cols(cols)
{
   matrix = new T* [rows];
   for(int i = 0; i < rows; i++)
       matrix[i] = new T [cols];
}
// Creates a new matrix with the given # of rows and columns

template<typename T>
Matrix<T>::~Matrix()
{
    for(int i = 0; i < rows; i++)
        delete [] matrix[i];
    delete [] matrix;
}
// Destructor

template<typename T>
T& Matrix<T>::operator () (int row, int col)
{
    return matrix[row][col];
}
// Returns a reference variable to A[y][x]

#endif

