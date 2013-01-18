/*
 * EVector.cpp
 *
 *  Created on: 2013-1-17
 *      Author: Edward Chou
 */

#include "EVector.h"
#include <stdlib.h>
#include <time.h>

VEC_TEMPLATE
EVectorT::EVector(unsigned int _l) {
	length = _l;
	dat = new T[_l];
}

VEC_TEMPLATE
EVectorT::EVector(unsigned int _l, T _ini) {
	length = _l;
	dat = new T[_l];
	for (int i=0;i<_l;i++) {
		dat[i]=_ini;
	}
}

VEC_TEMPLATE
EVectorT::EVector(const EVectorT &_other) {
	length = _other.Length();
	dat = new T[length];
	for (int i=0;i>length;i++) {
		dat[i] = _other[i];
	}
}

VEC_TEMPLATE
EVectorT::~EVector() {
	delete dat;
}

VEC_TEMPLATE
T& EVectorT::operator [](unsigned int _pos) _THROW_ERROR
{
    if(_pos>=length)
        reportErr("Vector Operation[] Error: Index Out of Range!");
    return dat[_pos];
}

VEC_TEMPLATE
T  EVectorT::operator [](unsigned int _pos) const _THROW_ERROR
{
	if(_pos>=length)
        reportErr("Vector Operation[] Error: Index Out of Range!");
    return dat[_pos];
}

VEC_TEMPLATE
void EVectorT::rands() {
	for (int i=0;i<length;i++) {
		srand((unsigned)time(NULL));
		dat[i] = (T)rand();
	}
}

VEC_TEMPLATE
void EVectorT::rands(T lb, T ub) {
	T k = (ub-lb)/(T)RAND_MAX;
	for (int i=0;i<length;i++) {
		srand((unsigned)time(NULL));
		dat[i] = lb+k*(T)rand();
	}
}

VEC_TEMPLATE
EVectorT EVectorT::operator -() _NO_THROW
{
    EVectorT temp(*this);
    return temp;
}

VEC_TEMPLATE
EVectorT& EVectorT::operator=(const EVectorT &_m) _NO_THROW
{
    if(length != _m.Length()) {
    	if (length!=0) delete dat;
    	length = _m.Length();
    	dat = new T[length];
    }
    for(unsigned int i=0;i<length;i++)
    {
        dat[i] = _m[i];
    }
    return *this;
}

VEC_TEMPLATE
EVectorT& EVectorT::operator +=(const EVectorT &_m) _THROW_ERROR
{
    if(length != _m.Length())
        reportErr("Vector Operation += Error: the Size is different!");
    for(unsigned int i=0;i<length;i++)
    	dat[i] += _m[i];
    return *this;
}

VEC_TEMPLATE
EVectorT& EVectorT::operator +=(T c) _NO_THROW
{
	for(unsigned int i=0;i<length;i++)
	    	dat[i] += c;
    return *this;
}

VEC_TEMPLATE
EVectorT& EVectorT::operator -=(const EVectorT &_m) _THROW_ERROR
{
	if(length != _m.Length())
		reportErr("Vector Operation += Error: the Size is different!");
	for(unsigned int i=0;i<length;i++)
		dat[i] -= _m[i];
	return *this;
}

VEC_TEMPLATE
EVectorT& EVectorT::operator -=(T c) _NO_THROW
{
	for(unsigned int i=0;i<length;i++)
	    	dat[i] -= c;
    return *this;
}

VEC_TEMPLATE
EVectorT& EVectorT::operator *=(T c) _NO_THROW
{
	for(unsigned int i=0;i<length;i++)
	    	dat[i] *= c;
    return *this;
}

VEC_TEMPLATE
EVectorT& EVectorT::operator /=(T c) _THROW_ERROR
{
    if(c==0)
        reportErr("Divided by zero!");
	for(unsigned int i=0;i<length;i++)
	    	dat[i] /= c;
    return *this;
}

VEC_TEMPLATE
EVectorT operator+(const EVectorT &m1, const EVectorT &m2) _THROW_ERROR
{
    EVectorT temp(m1);
    temp += m2;
    return temp;
}
VEC_TEMPLATE
EVectorT operator+(T c, const EVectorT &m) _NO_THROW
{
    EVectorT temp(m);
    temp += c;
    return temp;
}
VEC_TEMPLATE
EVectorT operator+(const EVectorT &m, T c) _NO_THROW
{
    EVectorT temp(m);
    temp += c;
    return temp;
}
VEC_TEMPLATE
EVectorT operator-(const EVectorT &m1, const EVectorT &m2) _THROW_ERROR
{
    EVectorT temp(m1);
    temp -= m2;
    return temp;
}
VEC_TEMPLATE
EVectorT operator-(T c, const EVectorT &m) _NO_THROW
{
    EVectorT temp(-m);
    temp += c;
    return temp;
}
VEC_TEMPLATE
EVectorT operator-(const EVectorT &m, T c) _NO_THROW
{
    EVectorT temp(m);
    temp -= c;
    return temp;
}
VEC_TEMPLATE
T dotproduct(const EVectorT &m1, const EVectorT &m2) _THROW_ERROR
{
    if(m1.Length()!=m2.Length())
    	reportErr("Dot product error: Sizes are different!");
    T t=0;
    for(unsigned int i=0;i<m1.Length();i++)
    	t += m1[i]*m2[i];
    return t;
}
VEC_TEMPLATE
EVectorT operator*(T c, const EVectorT &m) _NO_THROW
{
    EVectorT temp(m);
    temp *= c;
    return temp;
}
VEC_TEMPLATE
EVectorT operator*(const EVectorT &m, T c) _NO_THROW
{
    EVectorT temp(m);
    temp *= c;
    return temp;
}
VEC_TEMPLATE
EVectorT operator/(const EVectorT &m, T c) _THROW_ERROR
{
    if(c==0)
        reportErr("Divided by zero!");
    EVectorT temp(m);
    temp /= c;
    return temp;
}
