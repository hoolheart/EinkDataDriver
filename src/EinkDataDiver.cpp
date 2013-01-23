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
using namespace Eigen;

void testEigen();

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	//testing modules
	testEigen();

	return 0;
}

void testEigen() {
	cout <<"Testing the Eigen library."<<endl;
	MatrixXd m1(4,4);
	m1 << 1,2,3,4,
		  9,67,9.098,213,
		  80,23,98,7,
		  0,0,1,0;
	cout << m1 << endl;
	cout << "The trace of m1 is " << m1.trace() << endl;
	cout << "The determinant of m1 is " << m1.determinant() << endl;
	cout << "The first matrix 4*4." << endl;
	MatrixXd m2 = MatrixXd::Random(4,4);
	cout << m2<<endl<<m1+m2<<endl;
	m1 -=m2;
	m1 *=m2;
	cout << m1 <<endl;
	cout << "The inverse matrix of m1 is" << endl << m1.inverse() << endl;

	Matrix3f A;
	Vector3f b;
	A << 1,2,3, 4,5,6, 7,8,10;
	b << 3, 3, 4;
	cout << "Here is the matrix A:\n" << A << endl;
	cout << "Here is the vector b:\n" << b << endl;
	Vector3f x = A.colPivHouseholderQr().solve(b);
	cout << "The solution is:\n" << x << endl;
	cout << "The dot product of b and x is " << b.dot(x) << endl;
	cout << "The cross product of b and x is " << b.cross(x) << endl;
}
