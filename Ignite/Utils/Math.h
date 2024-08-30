#pragma once
#include <cmath>

class Vector2
{
public:
	float x, y;

	Vector2();
	Vector2(float x, float y);

	Vector2 operator+(const Vector2& other) const;

	Vector2 operator-(const Vector2& other) const;

	Vector2 operator*(float scaler) const;

	Vector2 operator/(float scaler) const;

	bool operator==(const Vector2& other) const;

	Vector2 Lerp(const Vector2& start, const Vector2& end, float t) const;
};

class Vector3
{
public:
	float x, y, z;

	Vector3();
	Vector3(float x, float y, float z);

	Vector3 operator+(const Vector3& other) const;

	Vector3 operator-(const Vector3& other) const;

	Vector3 operator*(float scaler) const;

	Vector3 operator/(float scaler) const;

	bool operator==(const Vector3& other) const;

	Vector3 Lerp(const Vector3& start, const Vector3& end, float t) const;
};