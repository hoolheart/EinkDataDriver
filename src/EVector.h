/*
 * EVector.h
 *
 *  Created on: 2013-1-17
 *      Author: Edward Chou
 */

#ifndef EVECTOR_H_
#define EVECTOR_H_
#include "EException.h"

/*
 * Class Name: EVector
 * Function:
 *   1. Record Data of a Vector
 *   2. Generate Special Vectors
 *   3. Achieve Basic Operations,
 *      e.g. Addition, Subtraction, Multiplication
 */
#ifndef _NO_TEMPLATE
#define VEC_TEMPLATE  template <class T>
#define EVectorT  EVector<T>
#else
#define VEC_TEMPLATE
#define EVectorT  EVector
#ifdef MATRIX_TYPE
     typedef MATRIX_TYPE T;
#else
     typedef double T;
#endif
#endif

VEC_TEMPLATE
class EVector {
private:
	T dat[];
	unsigned int length;
public:
	explicit EVector(unsigned int _l=0);
	explicit EVector(unsigned int _l, T _ini);
	explicit EVector(const EVectorT &_other);
	~EVector();
    T& operator [] (unsigned int _posl) _THROW_ERROR;
    T  operator [] (unsigned int _pos) const _THROW_ERROR;
	unsigned int Length() const {return length;}
	void rands();
	void rands(T lb, T ub);
    inline EVectorT operator+() _NO_THROW {return *this;}
    EVectorT operator-() _NO_THROW;
    EVectorT & operator=(const EVectorT &_m) _NO_THROW;
    EVectorT & operator+=(const EVectorT &_m) _THROW_ERROR;
    EVectorT & operator+=(T c) _NO_THROW;
    EVectorT & operator-=(const EVectorT &_m) _THROW_ERROR;
    EVectorT & operator-=(T c) _NO_THROW;
    EVectorT & operator*=(T c) _NO_THROW;
    EVectorT & operator/=(T c) _THROW_ERROR;
};

VEC_TEMPLATE
EVectorT operator+(const EVectorT &m1, const EVectorT &m2) _THROW_ERROR;
VEC_TEMPLATE
EVectorT operator+(T c, const EVectorT &m) _NO_THROW;
VEC_TEMPLATE
EVectorT operator+(const EVectorT &m, T c) _NO_THROW;
VEC_TEMPLATE
EVectorT operator-(const EVectorT &m1, const EVectorT &m2) _THROW_ERROR;
VEC_TEMPLATE
EVectorT operator-(T c, const EVectorT &m) _NO_THROW;
VEC_TEMPLATE
EVectorT operator-(const EVectorT &m, T c) _NO_THROW;
VEC_TEMPLATE
T dotproduct(const EVectorT &m1, const EVectorT &m2) _THROW_ERROR;
VEC_TEMPLATE
EVectorT operator*(T c, const EVectorT &m) _NO_THROW;
VEC_TEMPLATE
EVectorT operator*(const EVectorT &m, T c) _NO_THROW;
VEC_TEMPLATE
EVectorT operator/(const EVectorT &m, T c) _THROW_ERROR;

#endif /* EVECTOR_H_ */
