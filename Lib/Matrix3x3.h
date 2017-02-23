/******************************************************************************/
/*!
\file		Matrix3x3.h
\author 	DigiPen
\par    	email: ehosry\@digipen.edu
\date   	January 01, 2014
\brief

Copyright (C) 2014 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#ifndef _MATRIX3X3_H_
#define _MATRIX3X3_H_

#include "DataType.h"
#include "Vector2.h"

#ifdef _MSC_VER
// Supress warning: nonstandard extension used : nameless struct/union
#pragma warning( disable : 4201 )
#endif

///**************************************************************************/
///*!
//This function creates a translation matrix from x & y
//and saves it in pResult
//*/
///**************************************************************************/
//void Mtx33Translate(Matrix3x3 &pResult, float x, float y);
//
///**************************************************************************/
///*!
//This function creates a scaling matrix from x & y
//and saves it in pResult
//*/
///**************************************************************************/
//void Mtx33Scale(Matrix3x3 &pResult, float x, float y);
//
///**************************************************************************/
///*!
//This matrix creates a rotation matrix from "angle" whose value
//is in radian. Save the resultant matrix in pResult.
//*/
///**************************************************************************/
//void Mtx33RotRad(Matrix3x3 &pResult, float angle);
//
///**************************************************************************/
///*!
//This matrix creates a rotation matrix from "angle" whose value
//is in degree. Save the resultant matrix in pResult.
//*/
///**************************************************************************/
//void Mtx33RotDeg(Matrix3x3 &pResult, float angle);
//
///**************************************************************************/
///*!
//This functions calculated the transpose matrix of pMtx
//and saves it in pResult
//*/
///**************************************************************************/
//void Mtx33Transpose(Matrix3x3 &pResult, const Matrix3x3 &pMtx);
//
///**************************************************************************/
///*!
//This function calculates the inverse matrix of pMtx and saves the
//result in pResult. If the matrix inversion fails, pResult
//would be set to NULL.
//*/
///**************************************************************************/
////void Mtx33Inverse(Matrix3x3 *pResult, float *determinant, const Matrix3x3 &pMtx);
//
//void Mtx3x3Inverse(Matrix3x3 *pResult);

class Matrix3x3 {
public:
	Matrix3x3();
	Matrix3x3(const float *pArr);
	Matrix3x3(float _00, float _01, float _02,
		float _10, float _11, float _12,
		float _20, float _21, float _22);
	Matrix3x3& operator=(const Matrix3x3 &rhs);

	// Assignment operators
	Matrix3x3& operator *= (const Matrix3x3 &rhs);
	Matrix3x3 operator * (const Matrix3x3 &rhs) const;

	/**************************************************************************/
	/*!
	This operator multiplies the matrix pMtx with the vector rhs
	and returns the result as a vector
	*/
	/**************************************************************************/
	Vector2  operator * (const Vector2 &rhs) const;

	static Matrix3x3 Mtx33Identity();

	// Transforms
	

	float m[9];
};

#endif // CS230_MATRIX3X3_H_#pragma once
