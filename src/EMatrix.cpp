#include "EMatrix.h"
#include <stdlib.h>
#include <time.h>

MAT_TEMPLATE
EMatrixT::EMatrix()
{
    row = 0;
    col = 0;
    matVal = 0;
}

MAT_TEMPLATE
EMatrixT::EMatrix(unsigned int _row, unsigned int _col)
{
    row = 0;
    col = 0;
    matVal = 0;
    zeros(_row,_col);
}

MAT_TEMPLATE
EMatrixT::EMatrix(const EMatrixT &_m)
{
    row = _m.getRow();
    col = _m.getCol();
    matVal = new T*[row];
    for(unsigned int i=0;i<row;i++)
    {
        matVal[i] = new T[col];
        for(unsigned int j=0;j<col;j++)
            matVal[i][j] = _m(i,j);
    }
}

MAT_TEMPLATE
EMatrixT::~EMatrix()
{
    delMat();
}

MAT_TEMPLATE
void EMatrixT::delMat()
{
    if(!matVal)
    {
        for(unsigned int i=0;i<row;i++)
            delete []matVal[i];
        delete []matVal;
    }
    row = 0;
    col = 0;
    matVal = 0;
}

MAT_TEMPLATE
void EMatrixT::createMat(unsigned int _row, unsigned int _col)
{
    row = _row;
    col = _col;
    matVal = new T*[row];
    for(unsigned int i=0;i<row;i++)
        matVal[i] = new T[col];
}

MAT_TEMPLATE
T& EMatrixT::operator ()(unsigned int _row, unsigned int _col) _THROW_ERROR
{
    if((_row>=row)||(_col>=col))
        reportErr("Matrix Operation() Error: Index Out of Range!");
    return matVal[_row][_col];
}

MAT_TEMPLATE
T  EMatrixT::operator ()(unsigned int _row, unsigned int _col) const _THROW_ERROR
{
    if((_row>=row)||(_col>=col))
        reportErr("Matrix Operation() Error: Index Out of Range!");
    return matVal[_row][_col];
}

MAT_TEMPLATE
void EMatrixT::ones()
{
    if(row*col)
    {
        for(unsigned int i=0;i<row;i++)
            for(unsigned int j=0;j<col;j++)
                matVal[i][j] = 1;
    }
}

MAT_TEMPLATE
void EMatrixT::ones(unsigned int _row, unsigned int _col)
{
    delMat();
    createMat(_row,_col);
    ones();
}

MAT_TEMPLATE
void EMatrixT::zeros()
{
    if(row*col)
    {
        for(unsigned int i=0;i<row;i++)
            for(unsigned int j=0;j<col;j++)
                matVal[i][j] = 0;
    }
}

MAT_TEMPLATE
void EMatrixT::zeros(unsigned int _row, unsigned int _col)
{
    delMat();
    createMat(_row,_col);
    zeros();
}

MAT_TEMPLATE
void EMatrixT::rands()
{
    if(row*col)
    {
        for(unsigned int i=0;i<row;i++)
        {
            for(unsigned int j=0;j<col;j++)
            {
                srand((unsigned)time(NULL));
                matVal[i][j] = (T)rand();
            }
        }
    }
}

MAT_TEMPLATE
void EMatrixT::rands(unsigned int _row, unsigned int _col)
{
    delMat();
    createMat(_row,_col);
    rands();
}

MAT_TEMPLATE
void EMatrixT::unit(unsigned int _n)
{
    delMat();
    createMat(_n,_n);
    for(unsigned int i=0;i<row;i++)
    {
        for(unsigned int j=0;j<col;j++)
        {
            if(i == j)
                matVal[i][j] = 1;
            else
                matVal[i][j] = 0;
        }
    }
}

MAT_TEMPLATE
EMatrixT EMatrixT::operator -() _NO_THROW
{
    EMatrixT temp(row,col);
    temp -= *this;
    return temp;
}

MAT_TEMPLATE
EMatrixT& EMatrixT::operator=(const EMatrixT &_m) _NO_THROW
{
    delMat();
    row = _m.getRow();
    col = _m.getCol();
    matVal = new T*[row];
    for(unsigned int i=0;i<row;i++)
    {
        matVal[i] = new T[col];
        for(unsigned int j=0;j<col;j++)
            matVal[i][j] = _m(i,j);
    }
    return *this;
}

MAT_TEMPLATE
EMatrixT& EMatrixT::operator +=(const EMatrixT &_m) _THROW_ERROR
{
    if((row!=_m.getRow())||(col!=_m.getCol()))
        reportErr("Matrix Operation += Error: the Size is different!");
    for(unsigned int i=0;i<row;i++)
        for(unsigned int j=0;j<col;j++)
            matVal[i][j] += _m(i,j);
    return *this;
}

MAT_TEMPLATE
EMatrixT& EMatrixT::operator +=(T c) _NO_THROW
{
    for(unsigned int i=0;i<row;i++)
        for(unsigned int j=0;j<col;j++)
            matVal[i][j] += c;
    return *this;
}

MAT_TEMPLATE
EMatrixT& EMatrixT::operator -=(const EMatrixT &_m) _THROW_ERROR
{
    if((row!=_m.getRow())||(col!=_m.getCol()))
        reportErr("Matrix Operation -= Error: the Size is different!");
    for(unsigned int i=0;i<row;i++)
        for(unsigned int j=0;j<col;j++)
            matVal[i][j] -= _m(i,j);
    return *this;
}

MAT_TEMPLATE
EMatrixT& EMatrixT::operator -=(T c) _NO_THROW
{
    for(unsigned int i=0;i<row;i++)
        for(unsigned int j=0;j<col;j++)
            matVal[i][j] -= c;
    return *this;
}

MAT_TEMPLATE
EMatrixT& EMatrixT::operator *=(const EMatrixT &_m) _THROW_ERROR
{
    if(col!=_m.getRow())
        reportErr("Matrix Operation *= Error: the Size Don't Match!");
    EMatrixT temp(*this);
    delMat();
    createMat(temp.getRow(),_m.getCol());
    for(unsigned int i=0;i<row;i++)
        for(unsigned int j=0;j<col;j++)
        {
            T tempT = 0;
            for(unsigned int k=0;k<temp.getCol();k++)
                tempT += temp(i,k)*_m(k,j);
            matVal[i][j] = tempT;
        }
    return *this;
}

MAT_TEMPLATE
EMatrixT& EMatrixT::operator *=(T c) _NO_THROW
{
    for(unsigned int i=0;i<row;i++)
        for(unsigned int j=0;j<col;j++)
            matVal[i][j] *= c;
    return *this;
}

MAT_TEMPLATE
EMatrixT& EMatrixT::operator /=(T c) _THROW_ERROR
{
    if(c==0)
        reportErr("Divided by zero!");
    for(unsigned int i=0;i<row;i++)
        for(unsigned int j=0;j<col;j++)
            matVal[i][j] /= c;
    return *this;
}

MAT_TEMPLATE
EMatrixT operator+(const EMatrixT &m1, const EMatrixT &m2) _THROW_ERROR
{
    EMatrixT temp(m1);
    temp += m2;
    return temp;
}
MAT_TEMPLATE
EMatrixT operator+(T c, const EMatrixT &m) _NO_THROW
{
    EMatrixT temp(m);
    temp += c;
    return temp;
}
MAT_TEMPLATE
EMatrixT operator+(const EMatrixT &m, T c) _NO_THROW
{
    EMatrixT temp(m);
    temp += c;
    return temp;
}
MAT_TEMPLATE
EMatrixT operator-(const EMatrixT &m1, const EMatrixT &m2) _THROW_ERROR
{
    EMatrixT temp(m1);
    temp -= m2;
    return temp;
}
MAT_TEMPLATE
EMatrixT operator-(T c, const EMatrixT &m) _NO_THROW
{
    EMatrixT temp(-m);
    temp += c;
    return temp;
}
MAT_TEMPLATE
EMatrixT operator-(const EMatrixT &m, T c) _NO_THROW
{
    EMatrixT temp(m);
    temp -= c;
    return temp;
}
MAT_TEMPLATE
EMatrixT operator*(const EMatrixT &m1, const EMatrixT &m2) _THROW_ERROR
{
    EMatrixT temp(m1);
    temp *= m2;
    return temp;
}
MAT_TEMPLATE
EMatrixT operator*(T c, const EMatrixT &m) _NO_THROW
{
    EMatrixT temp(m);
    temp *= c;
    return temp;
}
MAT_TEMPLATE
EMatrixT operator*(const EMatrixT &m, T c) _NO_THROW
{
    EMatrixT temp(m);
    temp *= c;
    return temp;
}
MAT_TEMPLATE
EMatrixT operator/(const EMatrixT &m, T c) _THROW_ERROR
{
    if(c==0)
        reportErr("Divided by zero!");
    EMatrixT temp(m);
    temp /= c;
    return temp;
}
