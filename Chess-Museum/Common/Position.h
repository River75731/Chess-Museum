#pragma once
#include "Vector.h"

class Position2i;
class Position3i;

class Position2f {
protected:
	float x;
	float y;
public:
// Constructor & Destructor
	Position2f();
	Position2f(const float &x, const float &y);
	Position2f(const Position2f& that);
	explicit Position2f(const Vector2f& that);
	explicit Position2f(const Position2i& that);
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
public:
	// Constructor & Destructor
	Position2i();
	Position2i(const int &x, const int &y);
	Position2i(const Position2i& that);
	explicit Position2i(const Vector2i& that);
	explicit Position2i(const Position2f& that);
	~Position2i();
	// Get - Set Method
	const int getX() const;
	const int getY() const;
	Position2i& setX(const int& x);
	Position2i& setY(const int& y);
	// Operations
	Position2i operator+ (const Vector2i& that) const;
	Position2i operator- (const Vector2i& that) const;
	Vector2i operator- (const Position2i& that) const;
	bool operator== (const Position2i& that) const;
	bool operator!= (const Position2i& that) const;
	Position2i& operator= (const Position2i& that);
	Position2i& operator+=(const Vector2i& that);
	Position2i& operator-=(const Vector2i& that);
	bool inArea(const int& xmin, const int& ymin, const int& xlength, const int& ylength) const;
	Position2i& setInArea(const int& xmin, const int& ymin, const int& xlength, const int& ylength);
	bool inRange(const int& xmin, const int& ymin, const int& xmax, const int& ymax) const;
	Position2i& setInRange(const int& xmin, const int& ymin, const int& xmax, const int& ymax);
	// Output
	void output(const std::string &name = "DEFAULT") const;
};

class Position3i {
protected:
	int x;
	int y;
};