#pragma once

#include "DataType.h"
#include "Vector3.h"
#include <directxmath.h>
#include "Matrix3x3.h"

class Matrix4x4 {
public:
	Matrix4x4();
	Matrix4x4(const float *pArr);
	Matrix4x4(float _00, float _01, float _02, float _03,
		float _10, float _11, float _12, float _13,
		float _20, float _21, float _22, float _23,
		float _30, float _31, float _32, float _33);
	Matrix4x4(Matrix3x3 const& pMat);

	Matrix4x4& operator=(const Matrix4x4 &rhs);
	Matrix4x4& operator=(const Matrix3x3 &rhs);

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

	static Matrix4x4 Mtx44Identity();

	DirectX::XMMATRIX ToXMMatrix();

	// Transforms
	Matrix4x4 TRS(Vector3 const& Translate, float rotation, Vector3 const& scale);
	Matrix4x4 TRS(Vector3 const& Translate, Vector3 const& rotation, Vector3 const& scale);


	float m[16];
};