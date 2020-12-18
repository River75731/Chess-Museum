#pragma once
#include <iostream>
#include <string>
#include "MathBase.h"

class Vector2i;
class Vector3i;

class Vector2f {
protected:
	float x;
	float y;
public:
// Constructor & Destructor
	Vector2f();
	Vector2f(const float &x, const float &y);
	Vector2f(const Vector2f &that);
	explicit Vector2f(const Vector2i &that);
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
public:
	// Constructor & Destructor
	Vector2i();
	Vector2i(const int &x, const int &y);
	Vector2i(const Vector2i &that);
	explicit Vector2i(const Vector2f &that);	// type convert from Vector2f to Vector2i construct by rounding
	~Vector2i();
	// Get - Set Method
	const int getX() const;
	const int getY() const;
	Vector2i& setX(const int &x);
	Vector2i& setY(const int &y);
	const float getAngle() const; // get angle in degree
	const float getLength() const;
	// Operations 
	Vector2i operator+(const Vector2i& that) const;
	Vector2i operator-(const Vector2i& that) const;
	Vector2i operator-() const;
	Vector2i operator*(const int& that) const;
	Vector2i operator/(const int& that) const;
	bool operator==(const Vector2i& that) const;
	bool operator!=(const Vector2i& that) const;
	Vector2i& operator= (const Vector2i& that);
	Vector2i& operator+=(const Vector2i& that);
	Vector2i& operator-=(const Vector2i& that);
	Vector2i& operator*=(const int& that);
	Vector2i& operator/=(const int& that);
	const int dot(const Vector2i& that) const;			// dot product
	Vector2i& scale(const int &scaleX, const int &scaleY);
	Vector2i& rotate(const int& angle);	// rotate in degree only multiple of 90
	const float angle(const Vector2i& that) const;	// angle from this rotate to that (in degree)
// Output
	void output(const std::string &name = "DEFAULT") const;
};

class Vector3i {
protected:
	int x;
	int y;
	int z;
};