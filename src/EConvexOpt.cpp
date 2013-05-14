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
	isSolved = false;
	hasErr = false;
}

EConvexOpt::~EConvexOpt() {
	// clean up
}

bool EConvexOpt::setXDim(int _dim) {
	if (_dim>0) {
		xDim = _dim;
		return true;
	}
	else
		return false;
}

