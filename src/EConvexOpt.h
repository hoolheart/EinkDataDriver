/*
 * EConvexOpt.h
 *
 *  Created on: 15 mars 2013
 *      Author: Edward Chou
 */

#ifndef ECONVEXOPT_H_
#define ECONVEXOPT_H_
#include "type_def.h"
#include <string>
using namespace std;

/**
 * class: EConvexOpt
 * objective: solve convex optimization problems
 */

class EConvexOpt {
public:
	EConvexOpt();
	virtual ~EConvexOpt();
	typedef enum ObjType {
		obj_linear,obj_quadratic,obj_func,obj_dfunc
	}OBJ_TYPE;
	typedef enum EquConstraintType {
		equ_hyperplane,equ_func,equ_dfunc
	}EQU_CONSTRAINT_TYPE;
	typedef enum InequConstraintType {
		in_polyhedron,in_upbound,in_downbound,in_lmi,in_quadratic,in_func,in_dfunc
	}INEQU_CONSTRAINT_TYPE;
private:
	typedef struct ObjVal {
		OBJ_TYPE type;
		void * dat;
	}OBJ_VAL;
	typedef struct EquConsVal {
		EQU_CONSTRAINT_TYPE type;
		void * dat;
	}EQU_CONSTRAINT;
	typedef struct InequConsVal {
		INEQU_CONSTRAINT_TYPE type;
		void * dat;
	}INEQU_CONSTRAINT;
	OBJ_VAL obj;
	EQU_CONSTRAINT equCons[];
	INEQU_CONSTRAINT inequCons[];
	int xDim;
	EVec x_opt;
	double p_opt;
	bool isSolved;
	bool hasErr;
	string error;
public:
	bool setXDim(int _dim);
};

#endif /* ECONVEXOPT_H_ */
