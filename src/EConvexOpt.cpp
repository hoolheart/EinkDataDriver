/*
 * EConvexOpt.cpp
 *
 *  Created on: 15 mars 2013
 *      Author: Edward Chou
 */

#include "EConvexOpt.h"

EConvexOpt::EConvexOpt() {
	// Initialize
	xDim = 0;
	p_opt = 0;
	hasObjective = false;
	isSolved = false;
	isFeasible = false;
}

EConvexOpt::~EConvexOpt() {
	// clean up
	removeObjective();
	removeAllConstraints();
}

void EConvexOpt::setObjective(OBJ_TYPE _t, void * _d) {
	removeObjective();
	bool hasErr = false;
	EVec *c;
	FUNC_QUADRATRIC * f2;
	switch (_t) {
	case obj_linear:
		c = new EVec(*((EVec *)_d));
		obj.dat = c;
		break;
	case obj_quadratic:
		f2 = new FUNC_QUADRATRIC;
		f2->P = ((FUNC_QUADRATRIC*)_d)->P;
		f2->b = ((FUNC_QUADRATRIC*)_d)->b;
		f2->c = ((FUNC_QUADRATRIC*)_d)->c;
		obj.dat = f2;
		break;
	case obj_func:
		obj.dat = _d;
		break;
	case obj_dfunc:
		addError("Error: obj_dfunc is reserved objective type.");
		hasErr = true;
		break;
	default:
		addError("Error: invalid objective type.");
		hasErr = true;
		break;
	}

	if(!hasErr) {
		obj.type = _t;
		hasObjective = true;
	}
}

void EConvexOpt::removeObjective() {
	if (hasObjective) {
		switch (obj.type) {
		case obj_linear:
			delete (EVec *)obj.dat;
			break;
		case obj_quadratic:
			delete (FUNC_QUADRATRIC*)obj.dat;
			break;
		case obj_func:
		case obj_dfunc:
		default:
			break;
		}
		hasObjective = false;
	}
}

void EConvexOpt::addEquConstraint(CONSTRAINT_EQU_TYPE _t, void * _d) {
	EQU_CONSTRAINT * _n = new EQU_CONSTRAINT;
	_n->type = _t;
	bool hasErr = false;
	FUNC_LINEAR * f;
	switch (_t) {
	case equ_hyperplane:
		f = new FUNC_LINEAR;
		f->A = ((FUNC_LINEAR *)_d)->A;
		f->b = ((FUNC_LINEAR *)_d)->b;
		_n->dat = f;
		break;
	case equ_func:
		_n->dat = _d;
		break;
	case equ_dfunc:
		addError("Error: equ_dfunc is reserved equality type.");
		hasErr = true;
		break;
	default:
		addError("Error: invalid equality type.");
		hasErr = true;
		break;
	}

	if(hasErr) {
		delete _n;
	}
	else {
		equCons.push_back(_n);
	}
}

void EConvexOpt::addInequConstraint(CONSTRAINT_INEQU_TYPE _t, void * _d) {
	INEQU_CONSTRAINT * _n = new INEQU_CONSTRAINT;
	_n->type = _t;
	bool hasErr = false;
	FUNC_LINEAR * f1;
	FUNC_QUADRATRIC * f2;
	EVec *b;
	switch (_t) {
	case in_polyhedron:
		f1 = new FUNC_LINEAR;
		f1->A = ((FUNC_LINEAR *)_d)->A;
		f1->b = ((FUNC_LINEAR *)_d)->b;
		_n->dat = f1;
		break;
	case in_quadratic:
		f2 = new FUNC_QUADRATRIC;
		f2->P = ((FUNC_QUADRATRIC*)_d)->P;
		f2->b = ((FUNC_QUADRATRIC*)_d)->b;
		f2->c = ((FUNC_QUADRATRIC*)_d)->c;
		_n->dat = f2;
		break;
	case in_upbound:
	case in_lowbound:
		b = new EVec(*((EVec *)_d));
		_n->dat = b;
		break;
	case in_lmi:
	case in_func:
		_n->dat = _d;
		break;
	case in_dfunc:
		addError("Error: in_dfunc is reserved inequality type.");
		hasErr = true;
		break;
	default:
		addError("Error: invalid equality type.");
		hasErr = true;
		break;
	}

	if(hasErr) {
		delete _n;
	}
	else {
		inequCons.push_back(_n);
	}
}

void EConvexOpt::removeAllConstraints() {
	while(!equCons.empty()) {
		EQU_CONSTRAINT * _n1 = equCons.back();
		switch (_n1->type) {
		case equ_hyperplane:
			delete (FUNC_LINEAR *)_n1->dat;
			break;
		case equ_func:
		case equ_dfunc:
		default:
			break;
		}
		delete _n1;
		equCons.pop_back();
	}
	while(!inequCons.empty()) {
		INEQU_CONSTRAINT * _n2 = inequCons.back();
		switch (_n2->type) {
		case in_polyhedron:
			delete (FUNC_LINEAR *)_n2->dat;
			break;
		case in_quadratic:
			delete (FUNC_QUADRATRIC *)_n2->dat;
			break;
		case in_upbound:
		case in_lowbound:
			delete (EVec *)_n2->dat;
			break;
		case in_lmi:
		case in_func:
		case in_dfunc:
		default:
			break;
		}
		delete _n2;
		inequCons.pop_back();
	}
}

