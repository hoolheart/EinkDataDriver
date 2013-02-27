/*
 * EInterpolation.cpp
 *
 *  Created on: 2013-2-6
 *      Author: Edward Chou
 */

#include "EInterpolation.h"
#include <math.h>
//#include <iostream>
//using namespace std;

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
	EVec2 k = A.colPivHouseholderQr().solve(b);
	a0 = k(0); a1 = k(1);
}

bool EInterpolation::thirdOrderSplineInterpolation(SPLINE_TYPE type) {
	solved = false; hasErr = false;
	int n = x.rows()-1;
	if(y.rows()!=n+1) {
		error = "Wrong size setting!";
		hasErr = true;
		return false;
	}
	EVec b(n+1);
	EMat A=EMat::Zero(n+1,n+1);
	for (int i=1;i<n;i++) {
		A(i,i-1) = 1.0/(x(i)-x(i-1));
		A(i,i) = 2.0/(x(i)-x(i-1))+2.0/(x(i+1)-x(i));
		A(i,i+1) = 1.0/(x(i+1)-x(i));
		b(i) = 3.0*((y(i)-y(i-1))/(x(i)-x(i-1))/(x(i)-x(i-1))
				+(y(i+1)-y(i))/(x(i+1)-x(i))/(x(i+1)-x(i)));
	}
	switch (type) {
	case natural:
		A(0,0) = 2.0/(x(1)-x(0));
		A(0,1) = 1.0/(x(1)-x(0));
		b(0) = 3.0*(y(1)-y(0))/(x(1)-x(0))/(x(1)-x(0));
		A(n,n-1) = 1.0/(x(n)-x(n-1));
		A(n,n) = 2.0/(x(n)-x(n-1));
		b(n) = 3.0*(y(n)-y(n-1))/(x(n)-x(n-1))/(x(n)-x(n-1));
		break;
	default:
		error = "Unknown type!";
		hasErr = true;
		return false;
	}
	EVec k = A.colPivHouseholderQr().solve(b);
	rst.resize(4,n);
	for (int i=0;i<n;i++) {
		double a0 = k(i)*(x(i+1)-x(i))-(y(i+1)-y(i));
		double a1 = -k(i+1)*(x(i+1)-x(i))+(y(i+1)-y(i));
		double t = (x(i+1)-x(i))*(x(i+1)-x(i));
		rst(0,i) = ((x(i+1)-x(i))*(y(i)*x(i+1)-y(i+1)*x(i))-x(i)*x(i+1)*(a0*x(i+1)-a1*x(i)))/t;
		rst(1,i) = ((a0-a1)*x(i)*x(i+1)+(x(i)+x(i+1))*(a0*x(i+1)-a1*x(i))+(x(i+1)-x(i))*(y(i+1)-y(i)))/t;
		rst(2,i) = -((a0-a1)*(x(i)+x(i+1))+a0*x(i+1)-a1*x(i))/t;
		rst(3,i) = (a0-a1)/t;
	}
	solved = true;
	return solved;
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
