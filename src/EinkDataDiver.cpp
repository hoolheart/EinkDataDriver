//============================================================================
// Name        : EinkDataDiver.cpp
// Author      : Edward Chou
// Version     :
// Copyright   : 
// Description : Data Driven Toolbox Test File
//============================================================================

#include <iostream>
#include "test.h"
using namespace std;
//using namespace Eigen;

void testEigen();
void testCurveFitting();
void testInterpolation();

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	//testing modules
//	testEigen();
//	testCurveFitting();
	testInterpolation();

	string tmp;
	cin >> tmp;
	cout << tmp;
	return 0;
}

void testInterpolation() {
	cout << "Test interpolation." << endl;
	EVec x(11),y(11);
	x << 0,1,2,3,4,5,6,7,8,9,10;
	y << 0,1,3,6,10,15,21,28,36,45,55;
	EInterpolation solver;
	solver.setX(x);
	cout<<"x ="<<endl<<x<<endl;
	solver.setY(y);
	cout<<"y ="<<endl<<y<<endl;
	if(solver.linearInterpolation()) {
		cout << "Result is" << endl;
		cout << solver.getResult() << endl;
		cout << "Result of y is" << endl;
		cout << solver.getValue(x) << endl;
	}
	else {
		cout << solver.getError() << endl;
	}
	if(solver.thirdOrderSplineInterpolation(EInterpolation::natural,NULL)) {
		cout << "Result is" << endl;
		cout << solver.getResult() << endl;
		cout << "Result of y is" << endl;
		cout << solver.getValue(x) << endl;
	}
	else {
		cout << solver.getError() << endl;
	}
//	double arg[2] = [0,0];
	double *arg = new double[2];
	arg[0] = 0; arg[1] = 0;
	if(solver.thirdOrderSplineInterpolation(EInterpolation::complete,arg)) {
		cout << "Result is" << endl;
		cout << solver.getResult() << endl;
		cout << "Result of y is" << endl;
		cout << solver.getValue(x) << endl;
	}
	else {
		cout << solver.getError() << endl;
	}
}

void testEigen() {
	cout <<"Testing the Eigen library."<<endl;
	EMat m1(4,4);
	m1 << 1,2,3,4,
		  9,67,9.098,213,
		  80,23,98,7,
		  0,0,1,0;
	cout << m1 << endl;
	cout << "The trace of m1 is " << m1.trace() << endl;
	cout << "The determinant of m1 is " << m1.determinant() << endl;
	cout << "The first matrix 4*4." << endl;
	EMat m2 = EMat::Random(4,4);
	cout << m2<<endl<<m1+m2<<endl;
	m1 -=m2;
	m1 *=m2;
	cout << m1 <<endl;
	cout << "The inverse matrix of m1 is" << endl << m1.inverse() << endl;

	EMat3 A;
	EVec3 b;
	A << 1,2,3, 4,5,6, 7,8,10;
	b << 3, 3, 4;
	cout << "Here is the matrix A:\n" << A << endl;
	cout << "Here is the vector b:\n" << b << endl;
	EVec3 x = A.colPivHouseholderQr().solve(b);
	cout << "The solution is:\n" << x << endl;
	cout << "The dot product of b and x is " << b.dot(x) << endl;
	cout << "The cross product of b and x is " << b.cross(x) << endl;
}

void testCurveFitting() {
	cout << "Test the curve fitting problem." << endl;
	EMat X(10,3);
	X << 4.38744359656398,2.76025076998578,7.51267059305653,
		3.81558457093008,6.79702676853675,2.55095115459269,
		7.65516788149002,6.55098003973841,5.05957051665142,
		7.95199901137063,1.62611735194631,6.99076722656686,
		1.86872604554379,1.18997681558377,8.90903252535799,
		4.89764395788231,4.98364051982143,9.59291425205444,
		4.45586200710900,9.59743958516081,5.47215529963803,
		6.46313010111265,3.40385726666133,1.38624442828679,
		7.09364830858073,5.85267750979777,1.49294005559057,
		7.54686681982361,2.23811939491137,2.57508254123736;
	EVec y(10);
	y << 54.0064767318934,40.4479605740932,57.1714387452515,
		49.7110850714922,50.9205571065880,68.1873787357699,
		62.8284864900416,26.6024478196792,37.5966641672263,30.8862267805778;
	ECurveFitting solver;
	solver.setDat(X);
	solver.setObj(y);
	cout << "X =" << endl;
	cout << X << endl;
	cout << "y =" << endl;
	cout << y << endl;
	if(solver.linearFitting()) {
		EVec r = solver.readResult();
		double s = solver.StandardDeviation();
		cout << "The result is" << endl;
		cout << r << endl;
		cout << "The standard deviation is " << s << endl;
	}
	else
		cout << "The solver failed." << endl;
}
