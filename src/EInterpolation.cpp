/*
 * EInterpolation.cpp
 *
 *  Created on: 2013-2-6
 *      Author: Edward Chou
 */

#include "EInterpolation.h"
#include <math.h>

EInterpolation::EInterpolation() {
	solved = false;
	hasErr = false;
}

EInterpolation::~EInterpolation() {
	//
}

bool EInterpolation::linearInterpolation() {
	solved = false; hasErr = false;
	int n = x.rows()-1;
	if(y.rows()!=n+1) {
		error = "Wrong size setting!";
		hasErr = true;
		return false;
	}
	rst.resize(2,n);
	for(int i=0;i<n;i++) {
		double a0,a1;
		linear2Point((double)x(i),(double)x(i+1),(double)y(i),(double)y(i+1),a0,a1);
		rst(0,i) = a0; rst(1,i) = a1;
	}
	solved = true;
	return solved;
}

void EInterpolation::linear2Point(double x1, double x2, double y1, double y2, double &a0, double &a1) {
	EMat2 A;
	EVec2 b;
	A << 1,x1,1,x2;
	b << y1,y2;
	EVec2 x = A.colPivHouseholderQr().solve(b);
	a0 = x(0); a1 = x(1);
}

bool EInterpolation::thirdOrderSplineInterpolation() {
	solved = false; hasErr = false;
	int n = x.rows()-1;
	if((y.rows()!=n+1) || (f.rows()!=n+1)) {
		error = "Wrong size setting!";
		hasErr = true;
		return false;
	}
	rst.resize(2,n);
	for(int i=0;i<n;i++) {
		epline2Point(i,i);
	}
	solved = true;
	return solved;
}

void EInterpolation::epline2Point(int i, int j) {
	EMat4 A;
	EVec4 b;
	A << 1,x(i),pow((double)x(i),2),pow((double)x(i),3),
		1,x(i+1),pow((double)x(i+1),2),pow((double)x(i+1),3),
		0,1,2*x(i),3*pow((double)x(i),2),
		0,1,2*x(i+1),3*pow((double)x(i+1),2);
	b << y(i),y(i+1),f(j),f(j+1);
	EVec4 r = A.colPivHouseholderQr().solve(b);
	for(int k=0;k<4;k++) {
		rst(k,i) = r(k);
	}
}

double EInterpolation::getValue(double p) {
	if(!solved) {
		error = "The problem is not solved yet."; hasErr = true;
		return 0;
	}
	int n=rst.cols();
	int m;
	if(p<(double)x(0)) {
		error = "Out of range."; hasErr = true;
		m=0;
	}
	else if(p>(double)x(n-1)) {
		error = "Out of range."; hasErr = true;
		m = n-1;
	}
	else {
		hasErr = false;
		for (m=0;m<n-1;m++) {
			if (p<(double)x(m+1)) break;
		}
	}
	double v = (double)rst(0,m);
	for (int i=1;i<rst.rows();i++) {
		v += (double)rst(i,m)*pow(p,i);
	}
	return v;
}
