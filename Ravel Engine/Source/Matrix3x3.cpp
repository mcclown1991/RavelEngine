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
Matrix3x3 operator * (const Matrix3x3 &lhs, const Matrix3x3 &rhs)
{
	Matrix3x3 m = lhs;
	m *= rhs;

	return m;
}

/**************************************************************************/
/*!
overloaded * operator for multiplying a vector and a matrix
*/
/**************************************************************************/
fVector2  operator * (const Matrix3x3 &pMtx, const fVector2 &rhs)
{
	fVector2 v;
	v.x = pMtx.m[0] * rhs.x + pMtx.m[1] * rhs.y + pMtx.m[2];

	v.y = pMtx.m[3] * rhs.x + pMtx.m[4] * rhs.y + pMtx.m[5];

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

/**************************************************************************/
/*!
This function creates a translation matrix from x & y
and saves it in pResult
*/
/**************************************************************************/
void Mtx33Translate(Matrix3x3 &pResult, float x, float y)
{
	pResult.m[0] = 1;
	pResult.m[1] = 0;
	pResult.m[2] = x;
	pResult.m[3] = 0;
	pResult.m[4] = 1;
	pResult.m[5] = y;
	pResult.m[6] = 0;
	pResult.m[7] = 0;
	pResult.m[8] = 1;
}

/**************************************************************************/
/*!
This function creates a scaling matrix from x & y
and saves it in pResult
*/
/**************************************************************************/
void Mtx33Scale(Matrix3x3 &pResult, float x, float y)
{
	pResult.m[0] = x;
	pResult.m[1] = 0;
	pResult.m[2] = 0;
	pResult.m[3] = 0;
	pResult.m[4] = y;
	pResult.m[5] = 0;
	pResult.m[6] = 0;
	pResult.m[7] = 0;
	pResult.m[8] = 1;
}

/**************************************************************************/
/*!
This matrix creates a rotation matrix from "angle" whose value
is in radian. Save the resultant matrix in pResult.
*/
/**************************************************************************/
void Mtx33RotRad(Matrix3x3 &pResult, float angle)
{
	//Mtx33Identity(pResult);
	Matrix3x3 m;
	Mtx33Identity(m);

	m.m00 = cosf(angle);
	m.m01 = -sinf(angle);
	m.m10 = sinf(angle);
	m.m11 = cosf(angle);

	pResult = m;
}

/**************************************************************************/
/*!
This matrix creates a rotation matrix from "angle" whose value
is in degree. Save the resultant matrix in pResult.
*/
/**************************************************************************/
void Mtx33RotDeg(Matrix3x3 &pResult, float angle)
{
	Mtx33RotRad(pResult, (PI / 180.0f) * angle);
}

/**************************************************************************/
/*!
This functions calculated the transpose matrix of pMtx
and saves it in pResult
*/
/**************************************************************************/
void Mtx33Transpose(Matrix3x3 &pResult, const Matrix3x3 &pMtx)
{
	Matrix3x3 m;

	for (int a = 0; a < 3; a++)
	{
		for (int b = 0; b < 3; b++)
		{
			m.m[b * 3 + a] = pMtx.m[a * 3 + b];
		}
	}

	pResult = m;
}

/**************************************************************************/
/*!
This function calculates the inverse matrix of pMtx and saves the
result in pResult. If the matrix inversion fails, pResult
would be set to NULL.
*/
/**************************************************************************/
void Mtx33Inverse(Matrix3x3 *pResult, float *determinant, const Matrix3x3 &pMtx)
{
	float x, y, z;

	x = pMtx.m[0] * (pMtx.m[4] * pMtx.m[8] - pMtx.m[5] * pMtx.m[7]);
	y = pMtx.m[1] * (pMtx.m[3] * pMtx.m[8] - pMtx.m[5] * pMtx.m[6]);
	z = pMtx.m[2] * (pMtx.m[3] * pMtx.m[7] - pMtx.m[4] * pMtx.m[6]);
	*determinant = x - y + z;

	if (*determinant == 0)
		pResult = nullptr;

	Matrix3x3 m;

	m.m[0] = pMtx.m[4] * pMtx.m[8] - pMtx.m[5] * pMtx.m[7];
	m.m[1] = pMtx.m[5] * pMtx.m[6] - pMtx.m[3] * pMtx.m[8];
	m.m[2] = pMtx.m[3] * pMtx.m[7] - pMtx.m[4] * pMtx.m[6];
	m.m[3] = pMtx.m[2] * pMtx.m[7] - pMtx.m[1] * pMtx.m[8];
	m.m[4] = pMtx.m[0] * pMtx.m[8] - pMtx.m[2] * pMtx.m[6];
	m.m[5] = pMtx.m[1] * pMtx.m[6] - pMtx.m[0] * pMtx.m[7];
	m.m[6] = pMtx.m[1] * pMtx.m[5] - pMtx.m[2] * pMtx.m[4];
	m.m[7] = pMtx.m[2] * pMtx.m[3] - pMtx.m[0] * pMtx.m[5];
	m.m[8] = pMtx.m[0] * pMtx.m[4] - pMtx.m[1] * pMtx.m[3];

	for (int i = 0; i < 3; i++)
	{
		m.m[i] /= *determinant;
		m.m[i + 3] /= *determinant;
		m.m[i + 6] /= *determinant;
	}


	*pResult = m;
}