#pragma once
#include <iostream>
#include <string>
#include "MathBase.h"

class Vector2f {
protected:
	float x;
	float y;
public:
// Constructor & Destructor
	Vector2f();
	Vector2f(const float &x, const float &y);
	Vector2f(const Vector2f &that);
	~Vector2f();
// Get - Set Method
	const float getX() const;
	const float getY() const;
	Vector2f& setX(const float &x);
	Vector2f& setY(const float &y);
	const float getAngle() const; // get angle in degree
	const float getLength() const;
// Operations 
	Vector2f operator+(const Vector2f& that) const;
	Vector2f operator-(const Vector2f& that) const;
	Vector2f operator-() const;
	Vector2f operator*(const float& that) const;
	Vector2f operator/(const float& that) const;
	bool operator==(const Vector2f& that) const;
	bool operator!=(const Vector2f& that) const;
	Vector2f& operator= (const Vector2f& that);
	Vector2f& operator+=(const Vector2f& that);
	Vector2f& operator-=(const Vector2f& that);
	Vector2f& operator*=(const float& that);
	Vector2f& operator/=(const float& that);
	const float dot(const Vector2f& that) const;			// dot product
	Vector2f& normalize();
	Vector2f& scale(const float &scaleX, const float &scaleY);
	Vector2f& rotate(const float& angle);	// rotate in degree
	const float angle(const Vector2f& that) const;	// angle from this rotate to that (in degree)
// Output
	void output(const std::string &name = "DEFAULT") const;
};

class Vector3f {
protected:
	float x;
	float y;
	float z;
};

class Vector2i {
protected:
	int x;
	int y;
};

class Vector3i {
protected:
	int x;
	int y;
	int z;
};