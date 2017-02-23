#pragma once

#include "DataType.h"

class Vector2 {
public:
	Vector2();
	Vector2(float32 X, float32 Y);
	Vector2(Vector2 const& r);

	/// Operators
	Vector2 operator-() const;
	Vector2 operator-(Vector2 const& r) const;
	Vector2 operator+(Vector2 const& r) const;
	Vector2 operator*(float32 scalar) const;
	Vector2 operator/(float32 scalar) const;

	bool operator!=(Vector2 const& r) const;
	bool operator==(Vector2 const& r) const;

	/// special operators
	/***************************************************************************/
	/*!
	\brief
		Dot Product Operator
	\param r
		this * r
	*/
	/***************************************************************************/
	float operator*(Vector2 const& r) const;
	/***************************************************************************/
	/*!
	\brief
		2D Cross Product, Geometric meaning is to get information of it's
		direction in respect to another vector, sequence matters here
	\param r
		this X r
	\return
		The "Z" value of the vector
	*/
	/***************************************************************************/
	float operator^(Vector2 const& r) const;


	/// Some helpful operations
	Vector2 Normalized() const;
	Vector2 Normalize();
	float Length();
	static float Distance(Vector2 const& a, Vector2 const& b);
	static Vector2 Lerp(Vector2 const& a, Vector2 const& b, float t);
	static Vector2 Max(Vector2 const& a, Vector2 const& b);
	static Vector2 Min(Vector2 const& a, Vector2 const& b);

	/// public variables
	float x, y, magnitude, sqmagnitude;
};