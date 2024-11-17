#pragma once

class Vector3 {
public:
	float x, y, z;

	// Constructors
	Vector3();
	Vector3(float x, float y, float z);

	// Operations
	Vector3 add(const Vector3& other) const;
	Vector3 sub(const Vector3& other) const;
	Vector3 mult(const Vector3& other) const;
	Vector3 div(const Vector3& other) const;

	// Operator overloads
	Vector3 operator+(const Vector3& other) const;
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator*(const Vector3& other) const;
	Vector3 operator/(const Vector3& other) const;
	Vector3 operator+=(const Vector3& other);
	Vector3 operator-=(const Vector3& other);
	Vector3 operator*=(const Vector3& other);
	Vector3 operator/=(const Vector3& other);
};