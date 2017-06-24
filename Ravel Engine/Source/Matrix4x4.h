#pragma once

#include "DataType.h"
#include "Vector3.h"

class Matrix4x4 {
public:
	Matrix4x4();
	Matrix4x4(const float *pArr);
	Matrix4x4(float _00, float _01, float _02, float _03,
		float _10, float _11, float _12, float _13,
		float _20, float _21, float _22, float _23,
		float _30, float _31, float _32, float _33);
	Matrix4x4& operator=(const Matrix4x4 &rhs);

	// Assignment operators
	Matrix4x4& operator *= (const Matrix4x4 &rhs);
	Matrix4x4 operator * (const Matrix4x4 &rhs) const;

	/**************************************************************************/
	/*!
	This operator multiplies the matrix pMtx with the vector rhs
	and returns the result as a vector
	*/
	/**************************************************************************/
	Vector2  operator * (const Vector2 &rhs) const;

	static Matrix4x4 Mtx33Identity();

	// Transforms


	float m[9];
};