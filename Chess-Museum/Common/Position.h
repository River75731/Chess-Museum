#pragma once
#include "Vector.h"

class Position2f {
protected:
	float x;
	float y;
public:
// Constructor & Destructor
	Position2f();
	Position2f(const float &x, const float &y);
	Position2f(const Vector2f& that);
	Position2f(const Position2f& that);
	~Position2f();
// Get - Set Method
	const float getX() const;
	const float getY() const;
	Position2f& setX(const float& x);
	Position2f& setY(const float& y);
// Operations
	Position2f operator+ (const Vector2f& that) const;
	Position2f operator- (const Vector2f& that) const;
	Vector2f operator- (const Position2f& that) const;
	bool operator== (const Position2f& that) const;
	bool operator!= (const Position2f& that) const;
	Position2f& operator= (const Position2f& that);
	Position2f& operator+=(const Vector2f& that);
	Position2f& operator-=(const Vector2f& that);
	bool inArea(const float& xmin, const float& ymin, const float& xlength, const float& ylength) const;
	Position2f& setInArea(const float& xmin, const float& ymin, const float& xlength, const float& ylength);
	bool inRange(const float& xmin, const float& ymin, const float& xmax, const float& ymax) const;
	Position2f& setInRange(const float& xmin, const float& ymin, const float& xmax, const float& ymax);
// Output
	void output(const std::string &name = "DEFAULT") const;
};

class Position3f {
protected:
	float x;
	float y;
	float z;
};

class Position2i {
protected:
	int x;
	int y;
};

class Position3i {
protected:
	int x;
	int y;
};