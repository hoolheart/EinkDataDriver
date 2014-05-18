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
#include <vector>
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
 *     errors - the strings describing the errors
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
	 * equ_func: f(x)=0
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
	typedef struct LinearFunc {
		EMat A;
		EVec b;
	}FUNC_LINEAR;
	typedef struct QuadratricFunc {
		EMat P;
		EVec b;
		EVec c;
	}FUNC_QUADRATRIC;
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
	vector<EQU_CONSTRAINT*> equCons;
	vector<INEQU_CONSTRAINT*> inequCons;
	int xDim;
	EVec x0;
	EVec x_opt;
	double p_opt;
	bool hasObjective;
	bool isFeasible;
	bool isSolved;
	vector<string> errors;
	void addError(const string & err) {errors.push_back(err);}
public:
	bool hasError() {return !errors.empty();}
	string popError() {
		string err="";
		if (!errors.empty()) {
			err = errors.back();
			errors.pop_back();
		}
		return err;
	}
	//bool setXDim(int _dim);
	void setObjective(OBJ_TYPE _t, void * _d);
	void removeObjective();
	void addEquConstraint(CONSTRAINT_EQU_TYPE _t, void * _d);
	void addInequConstraint(CONSTRAINT_INEQU_TYPE _t, void * _d);
	void removeAllConstraints();
	void setInitialX(const EVec &_x) {
		x0 = _x; xDim = (int)_x.rows();
		if(!isSolved) x_opt = _x;
	}
};

#endif /* ECONVEXOPT_H_ */
