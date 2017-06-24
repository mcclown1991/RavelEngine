/******************************************************************************/
/*!
\file		Matrix4x4.cpp
\author 	Sebastian Tan sebastian.tan
\par    	email: sebastian.tan\@digipen.edu
\date   	March 19, 2014
\brief

Copyright (C) 2014 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#include "Matrix4x4.h"
#include <math.h>

#define PI			3.14159265358f

Matrix4x4::Matrix4x4()
{
	m[0] = 1.0f;
	m[1] = 0.0f;
	m[2] = 0.0f;
	m[3] = 0.0f;
	m[4] = 0.0f;
	m[5] = 1.0f;
	m[6] = 0.0f;
	m[7] = 0.0f;
	m[8] = 0.0f;
	m[9] = 0.0f;
	m[10] = 1.0f;
	m[11] = 0.0f;
	m[12] = 0.0f;
	m[13] = 0.0f;
	m[14] = 0.0f;
	m[15] = 1.0f;

}

/**************************************************************************/
/*!
Non Default constructor, takes in an array[9]
*/
/**************************************************************************/
Matrix4x4::Matrix4x4(const float *pArr)
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
	m[9] = pArr[9];
	m[10] = pArr[10];
	m[11] = pArr[11];
	m[12] = pArr[12];
	m[13] = pArr[13];
	m[14] = pArr[14];
	m[15] = pArr[15];
}

/**************************************************************************/
/*!
Non Default constructor, takes in 9 floats in order of row then colum
*/
/**************************************************************************/
Matrix4x4::Matrix4x4(float _00, float _01, float _02, float _03,
	float _10, float _11, float _12, float _13,
	float _20, float _21, float _22, float _23,
	float _30, float _31, float _32, float _33)
{
	m[0] = _00;
	m[1] = _01;
	m[2] = _02;
	m[3] = _03;
	m[4] = _10;
	m[5] = _11;
	m[6] = _12;
	m[7] = _13;
	m[8] = _20;
	m[9] = _21;
	m[10] = _22;
	m[11] = _23;
	m[12] = _30;
	m[13] = _31;
	m[14] = _32;
	m[15] = _33;
}

/**************************************************************************/
/*!
overloaded assignment operator
*/
/**************************************************************************/
Matrix4x4& Matrix4x4::operator = (const Matrix4x4 &rhs)
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
	m[9] = rhs.m[9];
	m[10] = rhs.m[10];
	m[11] = rhs.m[11];
	m[12] = rhs.m[12];
	m[13] = rhs.m[13];
	m[14] = rhs.m[14];
	m[15] = rhs.m[15];

	return *this;
}

/**************************************************************************/
/*!
overloaded assignment operator for concatenating matrix
*/
/**************************************************************************/
Matrix4x4& Matrix4x4::operator *= (const Matrix4x4 &rhs)
{
	int a, b, c;
	Matrix4x4 temp(this->m);

	for (a = 0; a < 4; a++)
	{
		for (b = 0; b < 4; b++)
		{
			m[a * 4 + b] = 0;
			for (c = 0; c < 4; c++)
			{
				m[a * 4 + b] += temp.m[a * 4 + c] * rhs.m[c * 4 + b];
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
Matrix4x4 Matrix4x4::operator* (Matrix4x4 const& rhs) const
{
	Matrix4x4 m = *this;
	m *= rhs;

	return m;
}

/**************************************************************************/
/*!
overloaded * operator for multiplying a vector and a matrix
*/
/**************************************************************************/
Vector2  Matrix4x4::operator * (Vector2 const& rhs) const
{
	Vector2 v;
	v.x = m[0] * rhs.x + m[1] * rhs.y + m[2] * 1 + m[3] * 1;

	v.y = m[4] * rhs.x + m[5] * rhs.y + m[6] * 1 + m[7] * 1;

	return v;

}

/**************************************************************************/
/*!
creates an identity matrix
*/
/**************************************************************************/
void Mtx33Identity(Matrix4x4 &pResult)
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

Matrix4x4 Matrix4x4::Mtx33Identity()
{
	Matrix4x4 result;
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

///**************************************************************************/
///*!
//This function creates a translation matrix from x & y
//and saves it in pResult
//*/
///**************************************************************************/
//void Mtx33Translate(Matrix4x4 &pResult, float x, float y)
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
//void Mtx33Scale(Matrix4x4 &pResult, float x, float y)
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
//void Mtx33RotRad(Matrix4x4 &pResult, float angle)
//{
//	//Mtx33Identity(pResult);
//	Matrix4x4 m;
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
//void Mtx33RotDeg(Matrix4x4 &pResult, float angle)
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
//void Mtx33Transpose(Matrix4x4 &pResult, const Matrix4x4 &pMtx)
//{
//	Matrix4x4 m;
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
////void Mtx33Inverse(Matrix4x4 *pResult, float *determinant, const Matrix4x4 &pMtx)
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
////	Matrix4x4 m;
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
//void Mtx3x3Inverse(Matrix4x4 *pResult){
//	Matrix4x4 m = Matrix4x4(*pResult);
//	m.m01 = pResult->m10;
//	m.m10 = pResult->m01;
//	m.m[2] = -m.m[2];
//	m.m[5] = -m.m[5];
//
//	*pResult = m;
//}