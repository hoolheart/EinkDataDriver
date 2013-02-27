/*
 * ECurveFitting.h
 *
 *  Created on: 2013-1-29
 *      Author: Edward Chou
 */

#ifndef ECURVEFITTING_H_
#define ECURVEFITTING_H_
#include "type_def.h"

/*
 * class: ECurveFitting
 * objective: solve the curve fitting problem
 * parameters
 *     dat: the variable data, dimension: n*m
 *     obj: the objective data, dimension: n*1
 *     rst: the fitting result data, possible dimension: m*1
 *     s: the standard deviation with the fitting result
 *     solved: whether the problem is solved
 *     hasErr: whether there are some errors
 * functions
 *     linearFitting: solve the linear curve fitting problem
 *     polynamialFitting: solve the polynamial curve fitting problem
 *     functionFitting: solve the curve fitting with any predefined function
 */
class ECurveFitting {
private:
	EMat dat;
	EVec obj;
	EVec rst;
	double s;
	bool solved;
	bool hasErr;
	double lambda,v,err;
public:
	ECurveFitting();
	virtual ~ECurveFitting();
	EMat readDat() const {return dat;}
	EVec readObj() const {return obj;}
	EVec readResult() const {return rst;}
	double StandardDeviation() const {return s;}
	bool isSolved() const {return solved;}
	bool hasError() const {return hasErr;}
	void setDat(const EMat & _d);
	void setObj(const EVec & _o);
	bool linearFitting();
	bool polynomialFitting(int d);
	bool functionFitting(double (*foo[])(EVec),int d);
	void setParameters(double _lambda, double _err=0.001) {
		lambda = _lambda; err = _err;
	}
private:
	bool checkDimension(const EMat& _d, const EVec& _o);
	bool solveLinearFitting(const EMat& x, const EVec& y);
	double power(double x,int k) {
		if (k==0)
			return 1;
		else
			return x*power(x,k-1);
	}
};

#endif /* ECURVEFITTING_H_ */
