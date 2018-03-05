/******************************************************************************/
/*!
\file		Matrix3x3.cpp
\author 	Sebastian Tan sebastian.tan
\par    	email: sebastian.tan\@digipen.edu
\date   	March 19, 2014
\brief

Copyright (C) 2014 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#include "Matrix3x3.h"
#include <math.h>

#define PI			3.14159265358f

Matrix3x3::Matrix3x3()
{
	m[0] = 1;
	m[1] = 0;
	m[2] = 0;
	m[3] = 0;
	m[4] = 1;
	m[5] = 0;
	m[6] = 0;
	m[7] = 0;
	m[8] = 1;
}

/**************************************************************************/
/*!
Non Default constructor, takes in an array[9]
*/
/**************************************************************************/
Matrix3x3::Matrix3x3(const float *pArr)
{
	m[0] = pArr[0];
	m[1] = pArr[1];
	m[2] = pArr[2];
	m[3] = pArr[3];
	m[4] = pArr[4];
	m[5] = pArr[5];
	m[6] = pArr[6];
	m[7] = pArr[7];
	m[8] = pArr[8];
}

/**************************************************************************/
/*!
Non Default constructor, takes in 9 floats in order of row then colum
*/
/**************************************************************************/
Matrix3x3::Matrix3x3(float _00, float _01, float _02,
	float _10, float _11, float _12,
	float _20, float _21, float _22)
{
	m[0] = _00;
	m[1] = _01;
	m[2] = _02;
	m[3] = _10;
	m[4] = _11;
	m[5] = _12;
	m[6] = _20;
	m[7] = _21;
	m[8] = _22;
}

/**************************************************************************/
/*!
overloaded assignment operator
*/
/**************************************************************************/
Matrix3x3& Matrix3x3::operator = (const Matrix3x3 &rhs)
{
	m[0] = rhs.m[0];
	m[1] = rhs.m[1];
	m[2] = rhs.m[2];
	m[3] = rhs.m[3];
	m[4] = rhs.m[4];
	m[5] = rhs.m[5];
	m[6] = rhs.m[6];
	m[7] = rhs.m[7];
	m[8] = rhs.m[8];

	return *this;
}

/**************************************************************************/
/*!
overloaded assignment operator for concatenating matrix
*/
/**************************************************************************/
Matrix3x3& Matrix3x3::operator *= (const Matrix3x3 &rhs)
{
	int a, b, c;
	Matrix3x3 temp(this->m);

	for (a = 0; a < 3; a++)
	{
		for (b = 0; b < 3; b++)
		{
			m[a * 3 + b] = 0;
			for (c = 0; c < 3; c++)
			{
				m[a * 3 + b] += temp.m[a * 3 + c] * rhs.m[c * 3 + b];
			}
		}
	}

	return *this;
}

/**************************************************************************/
/*!
overloaded * operator for concatenation of 2 matrix
*/
/**************************************************************************/
Matrix3x3 Matrix3x3::operator* (Matrix3x3 const& rhs) const
{
	Matrix3x3 m = *this;
	m *= rhs;

	return m;
}

/**************************************************************************/
/*!
overloaded * operator for multiplying a vector and a matrix
*/
/**************************************************************************/
Vector2  Matrix3x3::operator * (Vector2 const& rhs) const
{
	Vector2 v;
	v.x = m[0] * rhs.x + m[1] * rhs.y + m[2];

	v.y = m[3] * rhs.x + m[4] * rhs.y + m[5];

	return v;

}

/**************************************************************************/
/*!
creates an identity matrix
*/
/**************************************************************************/
void Mtx33Identity(Matrix3x3 &pResult)
{
	pResult.m[0] = 1;
	pResult.m[1] = 0;
	pResult.m[2] = 0;
	pResult.m[3] = 0;
	pResult.m[4] = 1;
	pResult.m[5] = 0;
	pResult.m[6] = 0;
	pResult.m[7] = 0;
	pResult.m[8] = 1;
}

Matrix3x3 Matrix3x3::Mtx33Identity()
{
	Matrix3x3 result;
	result.m[0] = 1;
	result.m[1] = 0;
	result.m[2] = 0;
	result.m[3] = 0;
	result.m[4] = 1;
	result.m[5] = 0;
	result.m[6] = 0;
	result.m[7] = 0;
	result.m[8] = 1;
	return result;
}

Matrix3x3 Matrix3x3::TRS(Vector2 const & Translate, float Rotate, Vector2 const & Scale)
{
	Matrix3x3 mat;
	Vector2 right, up;
	Rotate = (3.14125f / 180.0f) * Rotate;
	up = Vector2(-sin(Rotate), cos(Rotate));
	right = Vector2(up.y, -up.x);

	mat.m[0] = right.x * Scale.x;
	mat.m[1] = up.x * Scale.y;
	mat.m[3] = right.y * Scale.x;
	mat.m[4] = up.y * Scale.y;

	mat.m[2] = Translate.x * 0.89f;
	mat.m[5] = Translate.y * 0.89f;

	return mat;
}

Matrix3x3 Matrix3x3::TRS(Vector2 const & Translate, Vector2 const & Rotate, Vector2 const & Scale)
{
	Matrix3x3 mat;

	float angle = acos(Rotate.Normalized() * Vector2(1, 0));

	Vector2 right, up;
	angle = (3.14125f / 180.0f) * angle;
	up = Vector2(-sin(angle), cos(angle));
	right = Vector2(up.y, -up.x);

	mat.m[0] = right.x * Scale.x;
	mat.m[1] = up.x * Scale.y;
	mat.m[3] = right.y * Scale.x;
	mat.m[4] = up.y * Scale.y;

	mat.m[2] = Translate.x * 0.89f;
	mat.m[5] = Translate.y * 0.89f;
	return mat;
}

Matrix3x3 Matrix3x3::LookAt(Vector2 const & from, Vector2 const & to, Vector2 const & up)
{
	// given the to, find the up for to
	Vector2 u = to - from;
	Vector2 v(-u.x, u.y);

	//align frame to new frame
	Matrix3x3 original;

	return Matrix3x3();
}

///**************************************************************************/
///*!
//This function creates a translation matrix from x & y
//and saves it in pResult
//*/
///**************************************************************************/
//void Mtx33Translate(Matrix3x3 &pResult, float x, float y)
//{
//	pResult.m[0] = 1;
//	pResult.m[1] = 0;
//	pResult.m[2] = x;
//	pResult.m[3] = 0;
//	pResult.m[4] = 1;
//	pResult.m[5] = y;
//	pResult.m[6] = 0;
//	pResult.m[7] = 0;
//	pResult.m[8] = 1;
//}
//
///**************************************************************************/
///*!
//This function creates a scaling matrix from x & y
//and saves it in pResult
//*/
///**************************************************************************/
//void Mtx33Scale(Matrix3x3 &pResult, float x, float y)
//{
//	pResult.m[0] = x;
//	pResult.m[1] = 0;
//	pResult.m[2] = 0;
//	pResult.m[3] = 0;
//	pResult.m[4] = y;
//	pResult.m[5] = 0;
//	pResult.m[6] = 0;
//	pResult.m[7] = 0;
//	pResult.m[8] = 1;
//}
//
///**************************************************************************/
///*!
//This matrix creates a rotation matrix from "angle" whose value
//is in radian. Save the resultant matrix in pResult.
//*/
///**************************************************************************/
//void Mtx33RotRad(Matrix3x3 &pResult, float angle)
//{
//	//Mtx33Identity(pResult);
//	Matrix3x3 m;
//	Mtx33Identity(m);
//
//	float cosine = cosf(angle);
//	float sine = sinf(angle);
//
//	m.m00 = cosine;
//	m.m01 = sine;
//	m.m10 = sine;
//	m.m11 = cosine;
//
//	pResult = m;
//}
//
///**************************************************************************/
///*!
//This matrix creates a rotation matrix from "angle" whose value
//is in degree. Save the resultant matrix in pResult.
//*/
///**************************************************************************/
//void Mtx33RotDeg(Matrix3x3 &pResult, float angle)
//{
//	Mtx33RotRad(pResult, (PI / 180.0f) * angle);
//}
//
///**************************************************************************/
///*!
//This functions calculated the transpose matrix of pMtx
//and saves it in pResult
//*/
///**************************************************************************/
//void Mtx33Transpose(Matrix3x3 &pResult, const Matrix3x3 &pMtx)
//{
//	Matrix3x3 m;
//
//	for (int a = 0; a < 3; a++)
//	{
//		for (int b = 0; b < 3; b++)
//		{
//			m.m[b * 3 + a] = pMtx.m[a * 3 + b];
//		}
//	}
//
//	pResult = m;
//}
//
///**************************************************************************/
///*!
//This function calculates the inverse matrix of pMtx and saves the
//result in pResult. If the matrix inversion fails, pResult
//would be set to NULL.
//*/
///**************************************************************************/
////void Mtx33Inverse(Matrix3x3 *pResult, float *determinant, const Matrix3x3 &pMtx)
////{
////	float x, y, z;
////
////	x = pMtx.m[0] * (pMtx.m[4] * pMtx.m[8] - pMtx.m[5] * pMtx.m[7]);
////	y = pMtx.m[1] * (pMtx.m[3] * pMtx.m[8] - pMtx.m[5] * pMtx.m[6]);
////	z = pMtx.m[2] * (pMtx.m[3] * pMtx.m[7] - pMtx.m[4] * pMtx.m[6]);
////	*determinant = x - y + z;
////
////	if (*determinant == 0)
////		pResult = nullptr;
////
////	Matrix3x3 m;
////
////	m.m[0] = pMtx.m[4] * pMtx.m[8] - pMtx.m[5] * pMtx.m[7];
////	m.m[1] = pMtx.m[5] * pMtx.m[6] - pMtx.m[3] * pMtx.m[8];
////	m.m[2] = pMtx.m[3] * pMtx.m[7] - pMtx.m[4] * pMtx.m[6];
////	m.m[3] = pMtx.m[2] * pMtx.m[7] - pMtx.m[1] * pMtx.m[8];
////	m.m[4] = pMtx.m[0] * pMtx.m[8] - pMtx.m[2] * pMtx.m[6];
////	m.m[5] = pMtx.m[1] * pMtx.m[6] - pMtx.m[0] * pMtx.m[7];
////	m.m[6] = pMtx.m[1] * pMtx.m[5] - pMtx.m[2] * pMtx.m[4];
////	m.m[7] = pMtx.m[2] * pMtx.m[3] - pMtx.m[0] * pMtx.m[5];
////	m.m[8] = pMtx.m[0] * pMtx.m[4] - pMtx.m[1] * pMtx.m[3];
////
////	for (int i = 0; i < 3; i++)
////	{
////		m.m[i] /= *determinant;
////		m.m[i + 3] /= *determinant;
////		m.m[i + 6] /= *determinant;
////	}
////
////
////	*pResult = m;
////}
//
//void Mtx3x3Inverse(Matrix3x3 *pResult){
//	Matrix3x3 m = Matrix3x3(*pResult);
//	m.m01 = pResult->m10;
//	m.m10 = pResult->m01;
//	m.m[2] = -m.m[2];
//	m.m[5] = -m.m[5];
//
//	*pResult = m;
//}