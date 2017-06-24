#pragma once

#include "DataType.h"
#include "Vector2.h"

class Vector3 {
public:
	Vector3();
	Vector3(float32 X, float32 Y, float32 Z);
	Vector3(Vector3 const& r);
	Vector3(Vector2 const& r);

	/// Operators
	Vector3 operator-() const;
	Vector3 operator-(Vector3 const& r) const;
	Vector3 operator+(Vector3 const& r) const;
	Vector3 operator*(float32 scalar) const;
	Vector3 operator/(float32 scalar) const;

	bool operator!=(Vector3 const& r) const;
	bool operator==(Vector3 const& r) const;

	/// special operators
	/***************************************************************************/
	/*!
	\brief
	Dot Product Operator
	\param r
	this * r
	*/
	/***************************************************************************/
	float operator*(Vector3 const& r) const;
	/***************************************************************************/
	/*!
	\brief
	Cross Product, Unimplemented
	\param r
	this X r
	\return
	The "Z" value of the vector
	*/
	/***************************************************************************/
	float operator^(Vector3 const& r) const;


	/// Some helpful operations
	Vector3 Normalized() const;
	Vector3 Normalize();
	float Length();
	static float Distance(Vector3 const& a, Vector3 const& b);
	static Vector3 Lerp(Vector3 const& a, Vector3 const& b, float t);
	static Vector3 Max(Vector3 const& a, Vector3 const& b);
	static Vector3 Min(Vector3 const& a, Vector3 const& b);

	/// public variables
	float x, y, z, magnitude, sqmagnitude;
	Vector3* normalized;
};