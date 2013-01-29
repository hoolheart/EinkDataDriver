/*
 * type_def.h
 *
 *  Created on: 2013-1-29
 *      Author: Edward Chou
 */

#ifndef TYPE_DEF_H_
#define TYPE_DEF_H_

#ifndef NOT_EIGEN
#include "Eigen/Dense"
using namespace Eigen;
typedef MatrixXd EMat;
typedef VectorXd EVec;
typedef Matrix2d EMat2;
typedef Vector2d EVec2;
typedef Matrix3d EMat3;
typedef Vector3d EVec3;
typedef Matrix4d EMat4;
typedef Vector4d EVec4;
#endif

#endif /* TYPE_DEF_H_ */
