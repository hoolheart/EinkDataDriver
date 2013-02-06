/*
 * EInterpolation.h
 *
 *  Created on: 2013-2-6
 *      Author: Edward Chou
 */

#ifndef EINTERPOLATION_H_
#define EINTERPOLATION_H_
#include "type_def.h"
#include <string>
using namespace std;

/*
 * Class name: EInterpolation
 * Functionality: Solve the interpolation problem
 * Parameters:
 *     solved, whether the problem is solved;
 *     hasErr, whether there exist errors;
 *     error, the existing errors;
 *     x, the x vector;
 *     y, the y vector;
 *     f, the y' vector;
 *     rst, the solved matrix results.
 * Functions:
 *     linearInterpolation, solve linear interpolation problem;
 *     thirdOrderSplineInterpolation, solve the third order spline interpolation problem;
 *     getValue, get value in specific position after solving.
 */

class EInterpolation {
private:
	bool solved;
	bool hasErr;
	string error;
	EVec x,y,f;
	EMat rst;
public:
	EInterpolation();
	virtual ~EInterpolation();
	bool isSolved() const {return solved;}
	bool hasError() const {return hasErr;}
	string getError() const {return error;}
	void setX(const EVec &_x) {
		x.resize(_x.rows());
		x = _x;
	}
	void setY(const EVec &_y) {
		y.resize(_y.rows());
		y = _y;
	}
	void setYDifferential(const EVec &_f) {
		f.resize(_f.rows());
		f = _f;
	}
	EMat getResult() const {return rst;}
	bool linearInterpolation();
	bool thirdOrderSplineInterpolation();
	double getValue(double p);
private:
	void linear2Point(double x1, double x2, double y1, double y2, double &a0, double &a1);
	void epline2Point(int i, int j);
};

#endif /* EINTERPOLATION_H_ */
