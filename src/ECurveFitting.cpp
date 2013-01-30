/*
 * ECurveFitting.cpp
 *
 *  Created on: 2013-1-29
 *      Author: Edward Chou
 */

#include "ECurveFitting.h"
#include <math.h>
//#include <iostream>
//using namespace std;

ECurveFitting::ECurveFitting() {
	// TODO Auto-generated constructor stub
	solved = false;
	s = HUGE_VAL;
	hasErr = false;
	lambda = 1;
	v = 2;
	err = 0.001;
}

ECurveFitting::~ECurveFitting() {
	// TODO Auto-generated destructor stub
}

void ECurveFitting::setDat(const EMat& _d) {
	dat.resize(_d.rows(),_d.cols());
	dat = _d;
}

void ECurveFitting::setObj(const EVec& _o) {
	obj.resize(_o.rows());
	obj = _o;
}

bool ECurveFitting::linearFitting() {
	solved = false; hasErr = false;
	if(checkDimension(dat,obj)) {
		solved = solveLinearFitting(dat,obj);
	}
	else {
		hasErr = true;
	}
	return solved;
}

bool ECurveFitting::checkDimension(const EMat& _d, const EVec& _o) {
	if(_o.rows()==_d.rows() && _d.rows()>0 && _d.cols()>0)
		return true;
	else
		return false;
}

bool ECurveFitting::solveLinearFitting(const EMat& X, const EVec& y) {
	int n=X.rows(), m=X.cols();
	rst.resize(m+1);
	EMat J(n,m+1);
	J << EMat::Ones(n,1),X;
	EMat P = J.transpose()*J;
	if (P.determinant()!=0) {
		EVec b = y.transpose()*J;
		rst = P.colPivHouseholderQr().solve(b);
	}
	else {
		// apply Levenberg¨CMarquardt algorithm
		EMat I = P.diagonal().asDiagonal();
		EVec beta = EVec::Ones(m+1);
		// try lambda
		EVec d = (P+lambda*I).colPivHouseholderQr().solve(J.transpose()*(y-J*beta));
		EVec d2 = (P+lambda/v*I).colPivHouseholderQr().solve(J.transpose()*(y-J*beta));
		double dS = (d.transpose()*P*d+2*beta.transpose()*P*d-2*y.transpose()*J*d)(0,0);
		double dS2 = (d2.transpose()*P*d2+2*beta.transpose()*P*d2-2*y.transpose()*J*d2)(0,0);
		double l;
		if (dS<0) {
			if (dS<dS2) l = lambda; else {l = lambda/v; d = d2; dS = dS2;}
		}
		else if (dS2<0) {
			l = lambda/v; d = d2; dS = dS2;
		}
		else {
			l = lambda;
			int i;
			for (i=0;i<10;i++) {
				l *= v;
				d = (P+l*I).colPivHouseholderQr().solve(J.transpose()*(y-J*beta));
				dS = (d.transpose()*P*d+2*beta.transpose()*P*d-2*y.transpose()*J*d)(0,0);
				if (dS<0) break;
			}
			if (i==10) {
				hasErr = true;
				return false;
			}
		}
		int i;
		for (i=0;i<1000;i++) {
			beta += d;
			d = (P+l*I).colPivHouseholderQr().solve(J.transpose()*(y-J*beta));
			dS = (d.transpose()*P*d+2*beta.transpose()*P*d-2*y.transpose()*J*d)(0,0);
			if (fabs(dS)<err) break;
		}
		if (i==1000) {
			hasErr = true;
			return false;
		}
		rst = beta+d;
	}
	EVec e = y-J*rst;
	s = (e.transpose()*e)(0,0);
	s = sqrt(s);
	return true;
}

bool ECurveFitting::polynomialFitting(int d) {
	solved = false; hasErr = false;
	if(d>0 && checkDimension(dat,obj)) {
		int n=dat.rows(), m=dat.cols();
		EMat X(n,m*d);
		for (int i=0;i<n;i++) {
			for (int j=0;j<m;j++) {
				for (int k=0;k<d;k++) {
					X(i,j*m+k) = power((double)dat(i,j),2);
				}
			}
		}
		solved = solveLinearFitting(X,obj);
	}
	else
		hasErr = true;
	return solved;
}

bool ECurveFitting::functionFitting(double (*foo[])(EVec),int d) {
	solved = false; hasErr = false;
	if(d>0 && checkDimension(dat,obj)) {
		int n=dat.rows();
		EMat X(n,d);
		for (int i=0;i<n;i++) {
			for (int j=0;j<d;j++) {
				X(i,j) = (foo[j])(obj.row(i).transpose());
			}
		}
		solved = solveLinearFitting(X,obj);
	}
	else
		hasErr = true;
	return solved;
}
