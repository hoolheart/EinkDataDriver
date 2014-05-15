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
 * Parameters:
 *     obj - the objective function of the problem
 *     equCons - the equality constraints
 *     inequCons - the inequality constraints
 *     xDim - the dimension of variable x
 *     x_opt - the solved result
 *     p_opt - the value of optimized objective function
 *     isFeasible - the flag whether the problem is feasible
 *     isSolved - the flag whether the problem is solved
 *     hasErr - the flag whether there is any error in the process of solving
 *     error - the string describing the error
 * Methods:
 *     setXDim - set the dimension of the variable x
 */

class EConvexOpt {
public:
	EConvexOpt();
	virtual ~EConvexOpt();
	/**
	 * OBJ_TYPE: the type of objective variable
	 * obj_linear: c^T x
	 * obj_quadratic: x^T P x + b^T x
	 * obj_func: f(x)
	 * obj_dfunc: reserved
	 */
	typedef enum ObjType {
		obj_linear,obj_quadratic,obj_func,obj_dfunc
	}OBJ_TYPE;
	/**
	 * CONSTRAINT_EQU_TYPE: the type of equality constraint
	 * equ_hyperplane: Ax=b
	 * equ_func: f(x)=b
	 * equ_dfunc: reserved
	 */
	typedef enum EquConstraintType {
		equ_hyperplane,equ_func,equ_dfunc
	}CONSTRAINT_EQU_TYPE;
	/**
	 * CONSTRAINT_INEQU_TYPE: the type of inequality constraint
	 * in_polyhedron: Ax<=b
	 * in_upbound: x<=ub
	 * in_lowbound: x>=lb
	 * in_lmi: A(x) definite semi-positive
	 * in_quadratic: x^T A x + b^T x <= c
	 * in_func: f(x)<=0
	 * in_dfunc: reserved
	 */
	typedef enum InequConstraintType {
		in_polyhedron,in_upbound,in_lowbound,in_lmi,in_quadratic,in_func,in_dfunc
	}CONSTRAINT_INEQU_TYPE;
private:
	typedef struct ObjVal {
		OBJ_TYPE type;
		void * dat;
	}OBJ_VAL;
	typedef struct EquConsVal {
		CONSTRAINT_EQU_TYPE type;
		void * dat;
	}EQU_CONSTRAINT;
	typedef struct InequConsVal {
		CONSTRAINT_INEQU_TYPE type;
		void * dat;
	}INEQU_CONSTRAINT;
	OBJ_VAL obj;
	EQU_CONSTRAINT equCons[];
	INEQU_CONSTRAINT inequCons[];
	int xDim;
	EVec x_opt;
	double p_opt;
	bool isFeasible;
	bool isSolved;
	bool hasErr;
	string error;
public:
	bool setXDim(int _dim);
};

#endif /* ECONVEXOPT_H_ */
