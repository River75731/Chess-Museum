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
public:
	// Constructor & Destructor
	Vector3f();
	Vector3f(const float &x, const float &y, const float &z);
	Vector3f(const Vector3f &that);
	explicit Vector3f(const Vector3i &that);
	~Vector3f();
	// Get - Set Method
	const float getX() const;
	const float getY() const;
	const float getZ() const;
	Vector3f& setX(const float &x);
	Vector3f& setY(const float &y);
	Vector3f& setZ(const float &z);
	const float getLength() const;
	// Operations 
	Vector3f operator+(const Vector3f& that) const;
	Vector3f operator-(const Vector3f& that) const;
	Vector3f operator-() const;
	Vector3f operator*(const float& that) const;
	Vector3f operator/(const float& that) const;
	bool operator==(const Vector3f& that) const;
	bool operator!=(const Vector3f& that) const;
	Vector3f& operator= (const Vector3f& that);
	Vector3f& operator+=(const Vector3f& that);
	Vector3f& operator-=(const Vector3f& that);
	Vector3f& operator*=(const float& that);
	Vector3f& operator/=(const float& that);
	const float dot(const Vector3f& that) const;			// dot product
	Vector3f& normalize();
	Vector3f& scale(const float &scaleX, const float &scaleY, const float &scaleZ);
	// Output
	void output(const std::string &name = "DEFAULT") const;
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
public:
	// Constructor & Destructor
	Vector3i();
	Vector3i(const int &x, const int &y, const int &z);
	Vector3i(const Vector3i &that);
	explicit Vector3i(const Vector3f &that);	// type convert from Vector2f to Vector2i construct by rounding
	~Vector3i();
	// Get - Set Method
	const int getX() const;
	const int getY() const;	
	const int getZ() const;
	Vector3i& setX(const int &x);
	Vector3i& setY(const int &y);
	Vector3i& setZ(const int &z);
	const float getLength() const;
	// Operations 
	Vector3i operator+(const Vector3i& that) const;
	Vector3i operator-(const Vector3i& that) const;
	Vector3i operator-() const;
	Vector3i operator*(const int& that) const;
	Vector3i operator/(const int& that) const;
	bool operator==(const Vector3i& that) const;
	bool operator!=(const Vector3i& that) const;
	Vector3i& operator= (const Vector3i& that);
	Vector3i& operator+=(const Vector3i& that);
	Vector3i& operator-=(const Vector3i& that);
	Vector3i& operator*=(const int& that);
	Vector3i& operator/=(const int& that);
	const int dot(const Vector3i& that) const;			// dot product
	Vector3i& scale(const int &scaleX, const int &scaleY, const int &scaleZ);
// Output
	void output(const std::string &name = "DEFAULT") const;
};