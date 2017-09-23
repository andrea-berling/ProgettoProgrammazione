#ifndef MATRIX_H
#define MATRIX_H

template<typename T>
class Matrix
{
    protected:

        T** matrix;
        int cols;
        int rows;

    public:

        Matrix(const Matrix& m);
        // Copy constructor
        
        Matrix(int rows, int cols);
        // Creates a new matrix with the given # of rows and columns

        ~Matrix();
        // Destructor

        bool isEmpty(int i, int j);
        // Given two indexes i and j, returns true if matrix[i][j] == T()
        // Not much reliable with primitive data types

        T& operator () (int row, int col);
        // Returns a reference variable to A[row][col]

};

#include "../src/Matrix.cpp"

#endif
