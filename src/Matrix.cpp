#ifndef MATRIX_CPP
#define MATRIX_CPP
#include "../include/Matrix.h"

template<typename T>
Matrix<T>::Matrix(const Matrix& m):Matrix(m.rows,m.cols)
{
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
        {
            matrix[i][j] = m.matrix[i][j];
        }
}

template<typename T>
Matrix<T>::Matrix(const int rows, const int cols) : rows(rows), cols(cols)
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
T& Matrix<T>::operator () (const int row, const int col) const
{
    return matrix[row][col];
}
// Returns a reference variable to A[y][x]

template<typename T>
bool Matrix<T>::isEmpty(const int i, const int j)
{
    return matrix[i][j] == T();     // if i and j are invalid indexes, a segmentation fault error will occurr
    // Could implement differently with three return values(0 for false,1 for true, 2 for invalid indexes)
}
// Given two indexes i and j, returns true if matrix[i][j] == T()
#endif

