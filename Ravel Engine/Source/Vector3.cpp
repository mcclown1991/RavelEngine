#include "Vector3.h"

Vector3::Vector3() : x(0.f), y(0.f), z(0.f), magnitude(0.f), sqmagnitude(0.f), normalized(this) {}

Vector3::Vector3(float32 X, float32 Y, float32 Z) : x(X), y(Y), z(Z), magnitude(0.f), sqmagnitude(0.f), normalized(new Vector3(*this)) {
	sqmagnitude = x*x + y*y + z*z;
	
	if (sqmagnitude != 1) {
		magnitude = sqrtf(sqmagnitude);
		normalized->x = x / magnitude;
		normalized->y = y / magnitude;
		normalized->z = z / magnitude;
	}
	else {
		magnitude = 1;
	}

	//normalized->Normalize();
}

Vector3::Vector3(Vector3 const& r) : x(r.x), y(r.y), z(r.z), magnitude(r.magnitude), sqmagnitude(r.sqmagnitude) {}

Vector3::Vector3(Vector2 const& r) : x(r.x), y(r.y), z(0.f), magnitude(r.magnitude), sqmagnitude(r.sqmagnitude) {}

Vector3 Vector3::operator-() const {
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator-(Vector3 const& r) const {
	return Vector3(x - r.x, y - r.y, z - r.z);
}

Vector3 Vector3::operator+ (Vector3 const& r) const {
	return Vector3(x + r.x, y + r.y, z + r.z);
}

Vector3 Vector3::operator* (float32 scalar) const {
	return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 Vector3::operator/ (float32 scalar) const {
	return Vector3(x / scalar, y / scalar, z / scalar);
}

bool Vector3::operator!= (Vector3 const& r) const {
	return (x != r.x || y != r.y || z != r.z);
}

bool Vector3::operator== (Vector3 const& r) const {
	return (*this != r);
}

float Vector3::operator*(Vector3 const & r) const
{
	return x * r.x + y * r.y + z * r.z;
}

float Vector3::operator^(Vector3 const & r) const
{
	return x * r.y - y * r.x;
}

Vector3 Vector3::Normalized() const
{
	return Vector3(*this / magnitude);
}

Vector3 Vector3::Normalize()
{
	*this / magnitude;
	return *this;
}

float Vector3::Length()
{
	return magnitude;
}

float Vector3::Distance(Vector3 const& a, Vector3 const& b)
{
	float x = b.x - a.x;
	float y = b.y - a.y;
	float z = b.z - a.z;
	return sqrtf(x*x + y*y + z*z);
}

Vector3 Vector3::Lerp(Vector3 const & a, Vector3 const & b, float t)
{
	return Max(a, Min(a*(1 - t) + b*t, b));
}

Vector3 Vector3::Max(Vector3 const & a, Vector3 const & b)
{
	if (((a.x - b.x) + (a.y - b.y) + (a.z - b.z)) < ((b.x - a.x) + (b.y - a.y) + (b.z - a.z))) return b;
	else return a;
}

Vector3 Vector3::Min(Vector3 const & a, Vector3 const & b)
{
	if (((a.x - b.x) + (a.y - b.y) + (a.z - b.z)) > ((b.x - a.x) + (b.y - a.y) + (b.z - a.z))) return b;
	else return a;
}



