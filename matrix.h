#pragma once
#include "Vector3d.h"  

template<class MatrixType,  int MatrixColumns, int MatrixRows>
class Matrix {
public:
    MatrixType MatrixArray[MatrixColumns][MatrixRows];

    // initialize Matrix with value
    Matrix(MatrixType Value);

    //basic operations returning new matrix
    Matrix<MatrixType, MatrixColumns, MatrixRows> operator+(Matrix<MatrixType, MatrixColumns, MatrixRows> &Matrix2);
    Matrix<MatrixType, MatrixColumns, MatrixRows> operator-(Matrix<MatrixType, MatrixColumns, MatrixRows> &Matrix2);
    Matrix<MatrixType, MatrixColumns, MatrixRows> operator/(Matrix<MatrixType, MatrixColumns, MatrixRows> &Matrix2);
    Matrix<MatrixType, MatrixColumns, MatrixRows> operator*(Matrix<MatrixType, MatrixColumns, MatrixRows> &Matrix2);

    //basic operations returning same matrix
    Matrix<MatrixType, MatrixColumns, MatrixRows> &operator+=(Matrix<MatrixType, MatrixColumns, MatrixRows> &Matrix2);
    Matrix<MatrixType, MatrixColumns, MatrixRows> &operator-=(Matrix<MatrixType, MatrixColumns, MatrixRows> &Matrix2);
    Matrix<MatrixType, MatrixColumns, MatrixRows> &operator/=(Matrix<MatrixType, MatrixColumns, MatrixRows> &Matrix2);
    Matrix<MatrixType, MatrixColumns, MatrixRows> &operator*=(Matrix<MatrixType, MatrixColumns, MatrixRows> &Matrix2);

    //scalar operations
    Matrix<MatrixType, MatrixColumns, MatrixRows> &DivideByScalar(MatrixType Value);
    Matrix<MatrixType, MatrixColumns, MatrixRows> &MultiplyByScalar(MatrixType Value);

    //transpose Matrix
    Matrix<MatrixType, MatrixColumns, MatrixRows> &TransposeMatrix(void);

    // set up main diagonal
    Matrix<MatrixType, MatrixColumns, MatrixRows> &SetDiagonalMatrix(MatrixType Value);

    //get matrix info
    int GetMatrixRows(void);
    int GetMatrixColumns(void);

    MatrixType* GetMatrixRowArray(int Row);

    Vector3d<double> MovePoint(const Vector3d<double>& v) const;



};

template<class MatrixType, int MatrixColumns, int MatrixRows>
Matrix<MatrixType, MatrixColumns, MatrixRows>::Matrix(MatrixType Value)
{
    for (int i=0; i<MatrixRows; i++)
    {
        for (int j=0; j<MatrixColumns; j++)
        {
            this->MatrixArray[i][j] = Value;
        }
    }
}

template<class MatrixType, int MatrixColumns, int MatrixRows>
Matrix<MatrixType, MatrixColumns, MatrixRows>
&Matrix<MatrixType, MatrixColumns, MatrixRows>::operator+=(Matrix<MatrixType, MatrixColumns, MatrixRows> &Matrix2)
{
    for (int i = 0; i < MatrixRows; i++)
    {
        for (int j=0; j < MatrixColumns; j++)
        {
            this->MatrixArray[i][j] += Matrix2.MatrixArray[i][j];
        }
    }
    return *this;
}

template<class MatrixType,  int MatrixColumns, int MatrixRows>
Matrix<MatrixType, MatrixColumns, MatrixRows> Matrix<MatrixType, MatrixColumns, MatrixRows>::operator+(Matrix<MatrixType, MatrixColumns, MatrixRows> &Matrix2)
{
    return Matrix<MatrixType, MatrixColumns, MatrixRows>(*this).MatrixArray+=Matrix2;
}

template<class MatrixType, int MatrixColumns, int MatrixRows>
Matrix<MatrixType, MatrixColumns, MatrixRows> &Matrix<MatrixType, MatrixColumns, MatrixRows>::operator-=(Matrix<MatrixType, MatrixColumns, MatrixRows> &Matrix2)
{
    for (int i=0; i<MatrixRows; i++) {
        for (int j=0; j<MatrixColumns; j++) {
             this->MatrixArray[i][j] -= Matrix2.MatrixArray[i][j];
        }
    }
    return (*this).MatrixArray;
}


template<class MatrixType,  int MatrixColumns, int MatrixRows>
Matrix<MatrixType, MatrixColumns, MatrixRows> Matrix<MatrixType, MatrixColumns, MatrixRows>::operator-(Matrix <MatrixType, MatrixColumns, MatrixRows> &Matrix2)
{
    return Matrix<MatrixType, MatrixColumns, MatrixRows>(*this).MatrixArray-=Matrix2;
}

template<class MatrixType,  int MatrixColumns, int MatrixRows>
Matrix<MatrixType, MatrixColumns, MatrixRows> &Matrix<MatrixType, MatrixColumns, MatrixRows>::operator/=(Matrix <MatrixType, MatrixColumns, MatrixRows> &Matrix2)
{
    for (int i=0; i<MatrixRows; i++) {
        for (int j=0; j<MatrixColumns; j++) {
            this->MatrixArray[i][j]/=Matrix2.MatrixArray[i][j];
        }
    }
    return (*this).MatrixArray;
}

template<class MatrixType,  int MatrixColumns, int MatrixRows>
Matrix<MatrixType, MatrixColumns, MatrixRows> Matrix<MatrixType, MatrixColumns, MatrixRows>::operator/(Matrix<MatrixType, MatrixColumns, MatrixRows> &Matrix2)
{
    return Matrix<MatrixType, MatrixColumns, MatrixRows>(*this).MatrixArray/=Matrix2;
}

template<class MatrixType, int MatrixColumns, int MatrixRows>
Matrix<MatrixType, MatrixColumns, MatrixRows> &Matrix<MatrixType, MatrixColumns, MatrixRows>::operator*=(Matrix<MatrixType, MatrixColumns, MatrixRows> &Matrix2)
{
    for (int i = 0; i < MatrixRows; i++)
    {
        for (int j = 0; j < MatrixColumns; j++)
        {
            this->MatrixArray[i][j]*=Matrix2.MatrixArray[i][j];
        }
    }
    return (*this).MatrixArray;
}


template<class MatrixType, int MatrixColumns, int MatrixRows>
Matrix<MatrixType, MatrixColumns, MatrixRows> Matrix<MatrixType, MatrixColumns, MatrixRows>::operator*(Matrix<MatrixType, MatrixColumns, MatrixRows> &Matrix2)
{
    return Matrix<MatrixType, MatrixColumns, MatrixRows> (*this).MatrixArray*=Matrix2;
}

template<class MatrixType, int MatrixColumns, int MatrixRows>
Matrix<MatrixType, MatrixColumns, MatrixRows> &Matrix<MatrixType, MatrixColumns, MatrixRows>::DivideByScalar(MatrixType Value)
{
    for (int i = 0; i < MatrixRows; i++)
    {
        for (int j = 0; j < MatrixColumns; j++) {
            this->MatrixArray[i][j] /= Value;
        }
    }
    return (*this).MatrixArray;
};


template<class MatrixType, int MatrixColumns, int MatrixRows>
Matrix<MatrixType, MatrixColumns, MatrixRows> &Matrix<MatrixType, MatrixColumns, MatrixRows>::MultiplyByScalar(MatrixType Value)
{
    for (int i = 0; i < MatrixRows; i++) {
        for (int j = 0; j < MatrixColumns; j++) {
            this->MatrixArray[i][j] *= Value;
        }
    }
    return (*this).MatrixArray;
}

template<class MatrixType, int MatrixColumns, int MatrixRows>
Matrix<MatrixType, MatrixColumns, MatrixRows> &Matrix<MatrixType, MatrixColumns, MatrixRows>::TransposeMatrix()
{
    Matrix<MatrixType, MatrixColumns, MatrixRows> CurrentMatrix = (*this).MatrixArray->MatrixArray;
    for (int i = 0; i < MatrixRows; i++)
    {
        for (int j = 0; j < MatrixColumns; j++)
        {
            MatrixArray[i][j] = CurrentMatrix[j][i];
        }
    }
    (*this).MatrixArray->MatrixArray = CurrentMatrix;
    return (*this).MatrixArray;

}

template<class MatrixType, int MatrixColumns, int MatrixRows>
Matrix<MatrixType, MatrixColumns, MatrixRows> &Matrix<MatrixType, MatrixColumns, MatrixRows>::SetDiagonalMatrix(MatrixType Value)
{
    for (int i = 0; i < MatrixRows; i++)
    {
        for (int j = 0; j < MatrixColumns; j++)
        {
            if (j == i)
            {
                this->MatrixArray[i][j] = Value;
            }
        }
    }
    return (*this).MatrixArray;
}

template<class MatrixType, int MatrixColumns, int MatrixRows>
int Matrix<MatrixType, MatrixColumns, MatrixRows>::GetMatrixColumns() {
    return MatrixColumns;
}

template<class MatrixType, int MatrixColumns, int MatrixRows>
int Matrix<MatrixType, MatrixColumns, MatrixRows>::GetMatrixRows() {
    return MatrixRows;
}

template<class MatrixType, int MatrixColumns, int MatrixRows>
MatrixType* Matrix<MatrixType, MatrixColumns, MatrixRows>::GetMatrixRowArray(int Row)
{
    return MatrixArray[Row];
}

template<class MatrixType, int MatrixColumns, int MatrixRows>
Vector3d<double> 
Matrix<MatrixType, MatrixColumns, MatrixRows>::MovePoint(const Vector3d<double>& v) const
{
    static_assert(MatrixColumns == 4 && MatrixRows == 4 , "MovePoint only works on a 4x4 matrix");


    double resultX = ((*this).MatrixArray[0][0] * v.getVectorIndex(0)) + ((*this).MatrixArray[0][1] * v.getVectorIndex(1)) + ((*this).MatrixArray[0][2] * v.getVectorIndex(2)) + ((*this).MatrixArray[0][3]*1);
    double resultY = ((*this).MatrixArray[1][0] * v.getVectorIndex(0)) + ((*this).MatrixArray[1][1] * v.getVectorIndex(1)) + ((*this).MatrixArray[1][2] * v.getVectorIndex(2)) + ((*this).MatrixArray[1][3]*1);
    double resultZ = ((*this).MatrixArray[2][0] * v.getVectorIndex(0)) + ((*this).MatrixArray[2][1] * v.getVectorIndex(1)) + ((*this).MatrixArray[2][2] * v.getVectorIndex(2)) + ((*this).MatrixArray[2][3]*1);
    double resultW = ((*this).MatrixArray[3][0] * v.getVectorIndex(0)) + ((*this).MatrixArray[3][1] * v.getVectorIndex(1)) + ((*this).MatrixArray[3][2] * v.getVectorIndex(2)) + ((*this).MatrixArray[3][3]*1);

    Vector3d<double> Result( (resultX/resultW), (resultY/resultW), (resultZ/resultW) );

    return Result;

}
