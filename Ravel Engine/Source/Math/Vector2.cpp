#include "Vector2.h"

Vector2::Vector2() : x(0.f), y(0.f) {}

Vector2::Vector2(float32 X, float32 Y) : x(X), y(Y){}

Vector2::Vector2(Vector2 const& r) : x(r.x), y(r.y) {}

Vector2 Vector2::operator-() const{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator-(Vector2 const& r) const{
	return Vector2(x - r.x, y - r.y);
}

Vector2 Vector2::operator+ (Vector2 const& r) const{
	return Vector2(x + r.x, y + r.y);
}

Vector2 Vector2::operator* (float32 scalar) const{
	return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator/ (float32 scalar) const {
	return Vector2(x / scalar, y / scalar);
}

bool Vector2::operator!= (Vector2 const& r) const{
	return (x != r.x || y != r.y);
}

bool Vector2::operator== (Vector2 const& r) const{
	return (*this != r);
}

float Vector2::operator*(Vector2 const & r) const
{
	return x * r.x + y * r.y;
}

float Vector2::operator^(Vector2 const & r) const
{
	return x * r.y - y * r.x;
}

Vector2 Vector2::Normalized() const
{
	return Vector2(*this / Length());
}

Vector2 Vector2::Normalize()
{
	*this/Length();
	return *this;
}

float Vector2::Length() const
{
	float magnitude{};
	magnitude = x * x + y * y;
	magnitude = sqrt(magnitude);
	return magnitude;
}

float Vector2::SqLenght() const {
	return x * x + y * y;
}

float Vector2::Distance(Vector2 const& a, Vector2 const& b)
{
	float x = b.x - a.x;
	float y = b.y - a.y;
	return sqrtf(x*x + y*y);
}

Vector2 Vector2::Lerp(Vector2 const & a, Vector2 const & b, float t)
{
	return Max(a, Min(a*(1 - t) + b*t, b));
}

Vector2 Vector2::Max(Vector2 const & a, Vector2 const & b)
{
	if (((a.x - b.x) + (a.y - b.y)) < ((b.x - a.x) + (b.y - a.y))) return b;
	else return a;
}

Vector2 Vector2::Min(Vector2 const & a, Vector2 const & b)
{
	if (((a.x - b.x) + (a.y - b.y)) > ((b.x - a.x) + (b.y - a.y))) return b;
	else return a;
}

DirectX::XMFLOAT2 Vector2::ToXMFloat() {
	DirectX::XMFLOAT2 result;
	result.y = this->y;
	result.x = this->x;
	return result;
}

