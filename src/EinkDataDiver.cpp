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

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	//testing modules
	testEigen();
	testCurveFitting();

	return 0;
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
	X << 8.14723686393179,1.57613081677548,6.55740699156587,
		9.05791937075619,9.70592781760616,0.357116785741896,
		1.26986816293506,9.57166948242946,8.49129305868777,
		9.13375856139019,4.85375648722841,9.33993247757551,
		6.32359246225410,8.00280468888800,6.78735154857773,
		0.975404049994095,1.41886338627215,7.57740130578334,
		2.78498218867048,4.21761282626275,7.43132468124916,
		5.46881519204984,9.15735525189067,3.92227019534168,
		9.57506835434298,7.92207329559554,6.55477890177557,
		9.64888535199277,9.59492426392903,1.71186687811562;
	EVec y(10);
	y << 47.1207221896140,46.6485685667903,72.9990151656447,
		71.3427196881597,67.4122537545008,45.0995240109519,
		53.2527672904378,57.2799367478417,69.7671151170137,54.2743638451105;
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
