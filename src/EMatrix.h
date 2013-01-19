#ifndef EMATRIX_H
#define EMATRIX_H
#include <string.h>
#include "EException.h"

/*
 * Class Name: EMatrix
 * Author: Edward Chou
 * Function:
 *   1. Record Data of a Matrix
 *   2. Generate Special Matrixes
 *   3. Achieve Basic Operations,
 *      e.g. Addition, Subtraction, Multiplication
 *   4. Obtain Rank of a Matrix
 */
#ifndef _NO_TEMPLATE
#define MAT_TEMPLATE  template <class T>
#define EMatrixT  EMatrix<T>
#else
#define MAT_TEMPLATE
#define EMatrixT  EMatrix
#ifdef MATRIX_TYPE
     typedef MATRIX_TYPE T;
#else
     typedef double T;
#endif
#endif

MAT_TEMPLATE
class EMatrix
{
public:
    explicit EMatrix();
    explicit EMatrix(unsigned int _row, unsigned int _col);
    explicit EMatrix(const EMatrixT &_m);
    ~EMatrix();
private:
    void delMat();
    void createMat(unsigned int _row, unsigned int _col);

    /**
      Parameters:
        1. row, column: Size of Matrix
        2. matData: Data of Matrix
      */
private:
    unsigned int row,col;
    T ** matVal;

    /**
      Basic Operations:
        1. [a,b]: Get the Value Location (a,b) in Matrix
        2. getRow, getCol: Get the Size of Matrix
      */
    T& operator () (unsigned int _row, unsigned int _col) _THROW_ERROR;
    T  operator () (unsigned int _row, unsigned int _col) const _THROW_ERROR;
    unsigned int getRow() const {return row;}
    unsigned int getCol() const {return col;}

    /**
      Matrix Generator:
        1. ones: Each Member of Matrix is 1
        2. zeros: Each Member of Matrix is 0
        3. rand: Generate a Random Matrix
        4. unit: Generate a Unit Matrix
      */
public:
    void ones();
    void ones(unsigned int _row, unsigned int _col);
    void zeros();
    void zeros(unsigned int _row, unsigned int _col);
    void rands();
    void rands(unsigned int _row, unsigned int _col);
    void unit(unsigned int _n);

    /**
      Matrix Operation:
        1. -: Negate
        2. =: Assign a Value
        3. +=: Add a Number or Matrix to Self
        4. -=: Subtract a Number or Matrix to Self
        5. *=: Multiply a Number or Matrix to Self
        6. /=: Divide a Number or Matrix to Self
      */
public:
    inline EMatrixT operator+() _NO_THROW {return *this;}
    EMatrixT operator-() _NO_THROW;
    EMatrixT & operator=(const EMatrixT &_m) _NO_THROW;
    EMatrixT & operator+=(const EMatrixT &_m) _THROW_ERROR;
    EMatrixT & operator+=(T c) _NO_THROW;
    EMatrixT & operator-=(const EMatrixT &_m) _THROW_ERROR;
    EMatrixT & operator-=(T c) _NO_THROW;
    EMatrixT & operator*=(const EMatrixT &_m) _THROW_ERROR;
    EMatrixT & operator*=(T c) _NO_THROW;
    EMatrixT & operator/=(T c) _THROW_ERROR;

    /*
     * Other operators
     */
public:
    bool isSquare() {
    	if ((row!=0)&&(row==col))
    		return true;
    	else
    		return false;
    }
    void det() {
    	if(!isSquare())
    		reportErr("Matrix determinant error: not square!");
    }
};

MAT_TEMPLATE
EMatrixT operator+(const EMatrixT &m1, const EMatrixT &m2) _THROW_ERROR;
MAT_TEMPLATE
EMatrixT operator+(T c, const EMatrixT &m) _NO_THROW;
MAT_TEMPLATE
EMatrixT operator+(const EMatrixT &m, T c) _NO_THROW;
MAT_TEMPLATE
EMatrixT operator-(const EMatrixT &m1, const EMatrixT &m2) _THROW_ERROR;
MAT_TEMPLATE
EMatrixT operator-(T c, const EMatrixT &m) _NO_THROW;
MAT_TEMPLATE
EMatrixT operator-(const EMatrixT &m, T c) _NO_THROW;
MAT_TEMPLATE
EMatrixT operator*(const EMatrixT &m1, const EMatrixT &m2) _THROW_ERROR;
MAT_TEMPLATE
EMatrixT operator*(T c, const EMatrixT &m) _NO_THROW;
MAT_TEMPLATE
EMatrixT operator*(const EMatrixT &m, T c) _NO_THROW;
MAT_TEMPLATE
EMatrixT operator/(const EMatrixT &m, T c) _THROW_ERROR;

#endif // PMATRIX_H
