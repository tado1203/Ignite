#include "Math.h"

Vector2::Vector2() : x(0), y(0) {}
Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(float scaler) const
{
	return Vector2(x * scaler, y * scaler);
}

Vector2 Vector2::operator/(float scaler) const
{
	return Vector2(x / scaler, y / scaler);
}

bool Vector2::operator==(const Vector2& other) const
{
	return (x == other.x) && (y == other.y);
}

Vector2 Vector2::Lerp(const Vector2& start, const Vector2& end, float t) const
{
	return Vector2(start + (end - start) * t);
}

Vector3::Vector3() : x(0), y(0), z(0) {}
Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3 Vector3::operator+(const Vector3& other) const
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other) const
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator*(float scaler) const
{
	return Vector3(x * scaler, y * scaler, z * scaler);
}

Vector3 Vector3::operator/(float scaler) const
{
	return Vector3(x / scaler, y / scaler, z / scaler);
}

bool Vector3::operator==(const Vector3& other) const
{
	return x == other.x && y == other.y && z == other.z;
}

Vector3 Vector3::Lerp(const Vector3& start, const Vector3& end, float t) const
{
	return Vector3(start + (end - start) * t);
}